#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include <sys/socket.h>
#include <netinet/in.h>

#define SIZEBLOCK 1024*1024
char buffer[128];

#if 0
int read_pack(int sockfd,void * buf,size_t len)
{
	if(buf==NULL||len<=0)
		return 0;
	size_t nleft;
	size_t nread;
	char *ptr;
	ptr=(char *)buf;
	nleft=len;
	while(nleft>0)
	{
		if((nread=read(sockfd,ptr,nleft))<0)//read返回错误
		{
			if(errno==EINTR)//是由于信号中断造成的读失败，则继续读
				nread=0;
			else//否则是真正的读错误，返回失败的标志
				return -1;
		}
		else
		{
			if(nread==0)//数据读取完毕了，到达了文件的末尾
				break;
		}

		nleft-=nread;//剩余要读取的
		ptr+=nread;//偏移缓冲区位置
	}
	return (len-nleft);
}
#endif 

int _send(int sockfd, const void *buff, size_t nbytes, int flags)
{
    ssize_t ret = -1;
    do{
        if((ret=send(sockfd, buff, nbytes, flags)) < 0){
            return ret;
        }
        else if(ret == 0){
            return ret;
        }
        else if(ret < nbytes){
            nbytes -= ret;
            buff += ret;
            continue;
        }
        else 
            break;
    }while(1);

    return nbytes;
}

int main()
{
	int sockfd, len;
	struct sockaddr_in server_addr;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = 8888;
	inet_aton("192.168.1.111", &server_addr.sin_addr.s_addr);
	//inet_aton("127.0.0.1", &server_addr.sin_addr.s_addr);
	connect(sockfd, (struct sockaddr*)&server_addr, sizeof(struct sockaddr));

	memset(buffer, '\0', sizeof(buffer));
	strcpy(buffer, "hello server, start send data!!!\n");
    write(sockfd, buffer, sizeof(buffer));

    int blockNu = 1024;
    char data[SIZEBLOCK];
    memset(data, '2', SIZEBLOCK);
    char *p = data;

    int size = 1024;
    while(size-- > 0)
    {
        write(sockfd, data, sizeof(data));
    }

	memset(buffer, '\0', sizeof(buffer));
	strcpy(buffer, "end send data!\n");
    write(sockfd, buffer, sizeof(buffer));

	close(sockfd);
	return 0;
}
