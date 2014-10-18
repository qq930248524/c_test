#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

int sockfd;
char buf[128];
struct sockaddr_in server_addr;

void init_sock()
{
	memset(buf, '\0', sizeof(buf));
	sprintf(buf, "%s", "Hello , i am client!");
	memset(&server_addr, '\0', sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(8888);
	inet_aton("192.168.1.123", server_addr.sin_addr.s_addr);
	return ;
}

void fn_rec(int sockfd)
{
	char buf_rec[256];
	memset(buf_rec, '\0', sizeof(buf_rec));
	while(read(sockfd, buf_rec, sizeof(buf_rec)) != 0)
	{
		printf("<client_rec>:%s\n", buf_rec);
		memset(buf_rec, '\0', sizeof(buf_rec));
	}
	return;
}
void fn_sen(int sockfd)
{
	char buf_sen[256];
	memset(buf_sen, '\0', sizeof(buf_sen));
	while(gets(buf_sen) != NULL)
	{
		write(sockfd, buf_sen, sizeof(buf_sen));
		printf("<client_sen>:%s\n", buf_sen);
		memset(buf_sen, '\0', sizeof(buf_sen));
	}
	return;
}
void chat(int sockfd)
{
	pthread_t rec, sen;
	pthread_create(&rec, NULL, fn_rec, sockfd);
	pthread_create(&sen, NULL, fn_sen, sockfd);
	return ;
}

int main()
{
	init_sock();

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("Create socket error!\n");
		exit(1);
	}
	if(connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1)
	{
		perror("Connect socket error!\n");
		exit(1);
	}
	chat(sockfd);

	while(1)
	{}

	close(sockfd);
	return 1;
}
