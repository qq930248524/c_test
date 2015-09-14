#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <netinet/in.h>
#include <sys/socket.h>


#define SIZEBLOCK 1024*1024
FILE* infile;
unsigned long totalSize = 0;

int _recv(int sockfd, void *buff, size_t nbytes, int flags)
{
    ssize_t ret = -1;

    do{
        ret=read(sockfd, buff, nbytes);
        printf("ret = %d\n", ret);
        if(ret < 0){
            break;
        }
        else if(ret == 0){
            printf("ret = 0 ");
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
	if((infile = fopen("./test.dat", "a+")) == NULL)
		return;

	int numRead = 0;
	int sockfd, clientfd, len;
	len = sizeof(struct sockaddr);
	struct sockaddr_in server_addr, client_addr;
	char buffer[128];
    char data[SIZEBLOCK];
    char *p = &data[0];

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = 8888;
	server_addr.sin_addr.s_addr = INADDR_ANY;

	bind(sockfd, (struct sockaddr*)&server_addr, sizeof(struct sockaddr));
	listen(sockfd, 5);
	printf("Blocking...\n");
	clientfd = accept(sockfd, (struct sockaddr*)&client_addr, &len);

	memset(buffer, '\0', sizeof(buffer));
	numRead = read(clientfd, buffer, sizeof(buffer));
	printf("server receved:%dK\nbuf:%s\n", numRead/1024, buffer);


	memset(buffer, '\0', sizeof(buffer));
    numRead = 0;
    while(((numRead-1024*1024) < 0))
    {
	    numRead += recv(clientfd, data, 1024*1024, 0);
    }
	printf("server receved:%dK\n", numRead);

	memset(buffer, '\0', sizeof(buffer));
	numRead = read(clientfd, buffer, sizeof(buffer));
	printf("server receved:%dK\nbuf:%s\n", numRead, buffer);

	close(clientfd);
	close(sockfd);
	return 0;
}
