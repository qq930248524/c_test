
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <scsi/sg.h>


#define SCSI_TIMEOUT 5000 /* ms */

static char *device = "/dev/sda";

int scsi_io(int fd, unsigned char *cdb, unsigned char cdb_size, int xfer_dir,
            unsigned char *data, unsigned int *data_size,
            unsigned char *sense, unsigned int *sense_len)
{
    sg_io_hdr_t io_hdr;

    memset(&io_hdr, 0, sizeof(sg_io_hdr_t));
    io_hdr.interface_id = 'S';

    /* CDB */
    io_hdr.cmdp = cdb;
    io_hdr.cmd_len = cdb_size;

    /* Where to store the sense_data, if there was an error */
    io_hdr.sbp = sense;
    io_hdr.mx_sb_len = *sense_len;
    *sense_len=0;

    /* Transfer direction, either in or out. Linux does not yet
       support bidirectional SCSI transfers ?
     */
    io_hdr.dxfer_direction = xfer_dir;

    /* Where to store the DATA IN/OUT from the device and how big the
       buffer is
     */
    io_hdr.dxferp = data;
    io_hdr.dxfer_len = *data_size;

    /* SCSI timeout in ms */
    io_hdr.timeout = SCSI_TIMEOUT;


    if(ioctl(fd, SG_IO, &io_hdr) < 0){
        perror("SG_IO ioctl failed");
        return -1;
    }

    /* now for the error processing */
    if((io_hdr.info & SG_INFO_OK_MASK) != SG_INFO_OK){
        if(io_hdr.sb_len_wr > 0){
            *sense_len=io_hdr.sb_len_wr;
            return 0;
        }
    }
    if(io_hdr.masked_status){
        printf("status=0x%x\n", io_hdr.status);
        printf("masked_status=0x%x\n", io_hdr.masked_status);
        return -2;
    }
    if(io_hdr.host_status){
        printf("host_status=0x%x\n", io_hdr.host_status);
        return -3;
    }
    if(io_hdr.driver_status){
        printf("driver_status=0x%x\n", io_hdr.driver_status);
        return -4;
    }
    return 0;
}

int scsi_inquiry_unit_serial_number(int fd)
{
    unsigned char cdb[]={0x12,0x01,0x80,0,0,0};

    unsigned int data_size=0x00ff;
    unsigned char data[data_size];

    unsigned int sense_len=32;
    unsigned char sense[sense_len];

    int res, pl, i;

    cdb[3]=(data_size>>8)&0xff;
    cdb[4]=data_size&0xff;
    printf("cdn[3] = %d, cdb[4] = %d\n", cdb[3], cdb[4]);


    printf("INQUIRY Unit Serial Number:\n");

    res=scsi_io(fd, cdb, sizeof(cdb), SG_DXFER_FROM_DEV, data, &data_size, sense, &sense_len);
    if(res){
        printf("SCSI_IO failed\n");
        return -1;
    }
    if(sense_len){
        return -1;
    }

    /* Page Length */
    pl=data[3];

    /* Unit Serial Number */
    printf("Unit Serial Number:");
    for(i=4;i<(pl+4);i++)printf("%c",data[i]&0xff);printf("\n");
    return 0;
}

int open_scsi_device(const char *dev)
{
    int fd, vers;

    if((fd=open(dev, O_RDWR))<0){
        printf("ERROR could not open device %s\n", dev);
        return -1;
    }
    if ((ioctl(fd, SG_GET_VERSION_NUM, &vers) < 0) || (vers < 30000)) {
        printf("/dev is not an sg device, or old sg driver\n");
        close(fd);
        return -1;
    }

    return fd;
}

int main(int argc, const char *argv[])
{
    int fd;

    fd=open_scsi_device(device);
    if(fd<0){
        printf("Could not open SCSI device %s\n",device);
        _exit(10);
    }

    scsi_inquiry_unit_serial_number(fd);

    return 0;
}
