#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

int serverfd, clientfd;
int len_sockaddr;
char buf[256];
struct sockaddr_in server_addr, client_addr;

void init_sock()
{
	len_sockaddr = sizeof(struct sockaddr);
	memset(buf, '\0', sizeof(buf));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(8888);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	return;
}

void fn_rec(int sockfd)
{
	char buf_rec[256];
	while(read(sockfd, buf_rec, sizeof(buf_rec)) != 0)
	{
		printf("<server_rec>:%s\n", buf_rec);
		memset(buf_rec, '\0', sizeof(buf_rec));
	}
	return ;
}
void fn_sen(int sockfd)
{
	char buf_sen[256];
	while(gets(buf_sen) != NULL)
	{
		printf("<client_sen>:%s\n", buf_sen);
		write(sockfd, buf_sen, sizeof(buf_sen));
		memset(buf_sen, '\0', sizeof(buf_sen));
	}
	return;
}
void chat(int sockfd)
{
	pthread_t rec, sen;
	pthread_create(&rec, NULL, fn_rec, sockfd);
	pthread_create(&sen, NULL, fn_sen, sockfd);
	pthread_join(&rec, NULL);
	pthread_join(&sen, NULL);
	return ;
}

void create_sock(sockfd)
{
	init_sock();

	if((serverfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("Create socket error!");
		exit(1);
	}
	if(bind(serverfd, (struct sockaddr*)&server_addr, sizeof(struct sockaddr)) == -1)
	{
		perror("Bind socket error!");
		exit(2);
	}
	if(listen(serverfd, 5) == -1)
	{
		perror("Listen socket error!");
		exit(3);
	}
	if((clientfd = accept(serverfd, (struct sockaddr*)&client_addr, &len_sockaddr)) == -1)
	{
		perror("Accept socket error!");
		exit(4);
	}
}
int main()
{
	create_sock();
	chat(clientfd);

	close(serverfd);
	return 0;

}
