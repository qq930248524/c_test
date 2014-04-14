//transfer.c 
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void transfer(const char *in, char *out)
{
    int len1, len2;
    char *f1, *f2;
    //char *word1,*word2,*word3;
    f1 = strchr(in, ' ');
    f2 = strchr(f1+1, ' ');
    len1 = f1-in+1;
    len2 = f2-f1;
    char word1[len1];
    char word2[len2];
    memset(word1, 0, sizeof(word1));
    memset(word2, 0, sizeof(word2));
    snprintf(word1, len1, "%s", in);
    snprintf(word2, len2, "%s", f1+1);
    sprintf(out, "%s %s %s", f2+1, word2, word1);
    printf("len1:%d, len2:%d \n", len1, len2);
    printf("word1:%s, word2:%s \n", word1, word2);
}


int main()
{
    const char str1[] = "a bb ccc";
    int len = sizeof(str1);
    char str2[len];

    transfer(str1, str2);
    printf("str1:%s\n", str1);
    printf("str2:%s\n", str2);
    //printf("str2:%s\n", str2);

    return 0;

}
