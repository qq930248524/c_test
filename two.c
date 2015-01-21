#include <stdio.h>


int invert(int x, int p , int n)
{
	if(p > 32 || n > 32) return 0;
	int tmp = 0x01 << p;
	while(n--)
	{
		x ^= tmp;
		tmp = tmp >> 1;
	}
	return x;
}

typedef struct stu
{
	char name[8];
	int num;
}stu;

int main()
{
	int a;
	a = invert(2, 2, 2);
	printf("a = %d\n", a);


	return 0;
}
