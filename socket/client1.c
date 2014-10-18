#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <netinet/in.h>
#include <sys/socket.h>
pthread_t rec,sen;
static int FLAG = 1;

void fn_read(int sockfd)
{
	char buffer[256];
	while(read(sockfd, buffer, sizeof(buffer)) != 0)
	{
		printf("<client> read:%s\n", buffer);
		memset(buffer, '\0', sizeof(buffer));
	}
	return ;
}
void fn_write(int sockfd)
{
	char send_buf[256];
	while(gets(send_buf) != NULL)
	{
		printf("<client> write:%s\n", send_buf);
		write(sockfd, send_buf, strlen(send_buf));
		memset(send_buf, '\0', sizeof(send_buf));
	}
	return ;
}
void chitchat(int sockfd)
{
	pthread_create(&rec, NULL, fn_read, sockfd);
	pthread_create(&sen, NULL, fn_write, sockfd);
	return ;
}
int main()
{
	int sockfd,len;
	struct sockaddr_in server_addr;
	char buffer[256];

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("Create sockfd error:");
		error(1);
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(8888);
	inet_aton("192.168.1.123", &server_addr.sin_addr.s_addr);

	if(connect(sockfd, (struct sockaddr*)&server_addr, sizeof(struct sockaddr)) < 0)
	{
		perror("Connet error:");
		exit(2);
	}

#if 0
	memset(buffer, '\0', 256);
	strcpy(buffer, "Hello, I`m client, nice to meet u!\n");
	write(sockfd, buffer, strlen(buffer));
	printf("client:%s\n", buffer);
	memset(buffer, '\0', 256);
	read(sockfd, buffer, 256);
	printf("server:%s\n", buffer);
#endif

	chitchat(sockfd);
	while(FLAG == 1)
	{}

	close(sockfd);
	return 0;
}

