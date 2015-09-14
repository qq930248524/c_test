#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("over\n");
    execl("./t.sh", "t.sh", NULL);
    printf("over\n");
    return 0;
}
