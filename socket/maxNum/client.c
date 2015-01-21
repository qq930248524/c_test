#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <netinet/in.h>
char buffer[256];

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

void _send(int sockfd)
{
	char data[1024*1024*7];
	int numwrite = 0;
	memset(data, 1, sizeof(data));
	//write(sockfd, buffer, strlen(buffer));
	numwrite = write(sockfd, data, sizeof(data));
	sleep(12);
	printf("the num once write is %dk\n", numwrite/1024);
	
	return ;
}

int main()
{
	int sockfd, len;
	struct sockaddr_in server_addr;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = 8888;
	inet_aton("127.0.0.1", &server_addr.sin_addr.s_addr);
	//inet_aton("192.168.95.5", &server_addr.sin_addr.s_addr);

	connect(sockfd, (struct sockaddr*)&server_addr, sizeof(struct sockaddr));

	memset(buffer, '\0', sizeof(buffer));
	strcpy(buffer, "hello server, i`m client, nice to meet u!\n");
	//write(sockfd, buffer, strlen(buffer));
	_send(sockfd);



	memset(buffer, '\0', sizeof(buffer));
	read(sockfd, buffer, 256);
	printf("client said hello to server!\n");
	printf("server said:%s\n", buffer);

	close(sockfd);
	return 0;
}
