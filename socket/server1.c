#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <netinet/in.h>
#include <sys/socket.h>



void fn_write(int sockfd)
{
	char buf[256];
	while(gets(buf) != NULL)
	{
		printf("<server> write:%s\n", buf);
		write(sockfd, buf, sizeof(buf));
		memset(buf, '\0', sizeof(buf));
	}
	return;
}
void fn_read(int sockfd)
{
	char buf[256];
	while(read(sockfd, buf, sizeof(buf)) != 0)
	{
		printf("<server> read:%s\n", buf);
		memset(buf, '\0', sizeof(buf));
	}
	return;
}
void chitchat(int sockfd)
{
	pthread_t rec, sen;
	pthread_create(&rec, NULL, fn_read, sockfd);
	pthread_create(&sen, NULL, fn_write, sockfd);
	return;
}
int main()
{
	int sockfd, clientfd;
	int len_sockaddr = sizeof(struct sockaddr);
	struct sockaddr_in server_addr, client_addr;
	char buffer[256];
	memset(buffer, '\0', sizeof(buffer));

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("Create socket error:");
		exit(1);
	}
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = 8888;
	server_addr.sin_addr.s_addr = INADDR_ANY;

	bind(sockfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
	listen(sockfd, 5);
	clientfd = accept(sockfd, (struct sockaddr*)&client_addr, &len_sockaddr);

	chitchat(clientfd);
	while(1){}

	close(sockfd);
	close(clientfd);
	return 0;
}

//gcc server1.c -lpthread -o server
