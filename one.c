#include <stdio.h>
#include <stdlib.h>

#define uint8 char

typedef struct commond{
	//char cmd_id;
	int *info;
}Commond;

typedef Commond pcmd;

int main()
{
	Commond * cmd;
	struct commond test;
	cmd = &test;
	cmd->info=(void *)malloc(sizeof(Commond));
	char *a;

	printf("sizeof(tpyedef) = %ld\n", sizeof(a));
	printf("sizeof(tpyedef) = %ld\n", sizeof(struct commond));

	printf("sizeof(int) = %ld \n", sizeof(int));

	return 0;
}
