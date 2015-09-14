#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <linux/hdreg.h>

static int getdiskid (char *id, size_t max)
{
    int fd;
    struct hd_driveid hid;
    FILE *fp;
    char line[0x100], *disk; 
    char *root, *p;
    fp = fopen ("/etc/mtab", "r");
    if (fp == NULL)
    {
        fprintf (stderr, "No /etc/mtab file.\n");
        return -1;
    }
    fd = -1;
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        disk = strtok(line, " ");
        if (disk == NULL)
        {
            continue;
        }
        root = strtok (NULL, " ");
        if (root == NULL)
        {
            continue;
        }
        if (strcmp (root, "/") == 0)
        {
            for (p = disk + strlen (disk) - 1; isdigit (*p); p --)
            {
                *p = '\0';
            }
            disk = "/dev/sda";
            fd = open (disk, O_RDONLY);
            break;
        }
    }
    fclose (fp);
    if (fd < 0)
    {
        fprintf (stderr, "open hard disk device failed.\n");
        return -1;
    }
    if (ioctl (fd, HDIO_GET_IDENTITY, &hid) < 0)
    {
        fprintf (stderr, "ioctl error.\n");
        return -1;
    }
    close (fd);
    snprintf (id, max, "%s", hid.serial_no);
    fprintf (stdout, "get hard disk serial number: %s\n", id);
    return 0;
}


void main()
{
    char a[100];
    int max = 100;
    getdiskid(a, max);
    //printf("id:%s\n", a);
    return ;

}
