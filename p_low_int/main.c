#include <stdio.h>

void funp(int a)
{
    if(a>10){
        printf("%d ", a%10);
        funp(a/10);
    }
    else{
        printf("%d ", a);
    }
}


int main()
{
    int a = 12345;
    funp(a);
    return 1;
}
