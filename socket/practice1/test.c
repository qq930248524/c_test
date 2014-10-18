#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct test
{  
	int a;
	int b;
	char c[10];
};

void main()
{
	struct test t1;
	printf("sizeof(t1):%d\n", sizeof(t1));
	//printf("sizeof(test):%d\n", sizeof(test));
	printf("sizeof(struct test):%d\n", sizeof(struct test));
	memset(&t1, '\0', sizeof(t1));
	return;
}
