#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <netinet/in.h>
#include <sys/socket.h>

int main()
{
	int sockfd, clientfd, len;
	len = sizeof(struct sockaddr);
	struct sockaddr_in server_addr, client_addr;
	char buffer[256];

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = 8888;
	server_addr.sin_addr.s_addr = INADDR_ANY;

	bind(sockfd, (struct sockaddr*)&server_addr, sizeof(struct sockaddr));
	listen(sockfd, 5);
	printf("Blocking...\n");
	clientfd = accept(sockfd, (struct sockaddr*)&client_addr, &len);

	memset(buffer, '\0', 256);
	read(clientfd, buffer, 256);
	printf("server receved:%s\n", buffer);

	memset(buffer, '\0', 256);
	strcpy(buffer, "I have receved! Thanks!\n");
	write(clientfd, buffer, strlen(buffer));

	close(clientfd);
	close(sockfd);
	return 0;
}
