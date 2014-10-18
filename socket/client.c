#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <netinet/in.h>
char buffer[256];

void _send(int sockfd)
{
	write(sockfd, buffer, strlen(buffer));
	return ;
}

int main()
{
	int sockfd, len;
	struct sockaddr_in server_addr;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = 8888;
	//inet_aton("127.0.0.1", &server_addr.sin_addr.s_addr);
	inet_aton("192.168.95.5", &server_addr.sin_addr.s_addr);

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
