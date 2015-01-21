#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <netinet/in.h>
#include <sys/socket.h>

int main()
{
	FILE* infile;
	if((infile = fopen("./test.dat", "a+")) == NULL)
		return;

	int numRead = 0;
	int sockfd, clientfd, len;
	len = sizeof(struct sockaddr);
	struct sockaddr_in server_addr, client_addr;
	char buffer[1024*1024*7];

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = 8888;
	server_addr.sin_addr.s_addr = INADDR_ANY;

	bind(sockfd, (struct sockaddr*)&server_addr, sizeof(struct sockaddr));
	listen(sockfd, 5);
	printf("Blocking...\n");
	clientfd = accept(sockfd, (struct sockaddr*)&client_addr, &len);

	memset(buffer, '\0', sizeof(buffer));
	sleep(12);
	numRead = read(clientfd, buffer, sizeof(buffer));
	sleep(3);
	fwrite(buffer, 1, sizeof(buffer), infile);
	printf("server receved:%dK\n", numRead/1024);


	memset(buffer, '\0', sizeof(buffer));
	strcpy(buffer, "I have receved! Thanks!\n");
	write(clientfd, buffer, strlen(buffer));

	close(clientfd);
	close(sockfd);
	return 0;
}
