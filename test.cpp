#include <stdio.h>
#include <regex.h>
char pattern[110],str[110];
int main()
{
    regex_t re;
    int cflags = REG_NOSUB;
    int status;
    while(scanf("%s%s",pattern+1,str+1) != EOF)
    {
        regcomp(&re,pattern,cflags);
        status = regexec(&re,str,0,NULL,0);
        if(status == 0)
            puts("Yes");
        else
            puts("No");
        regfree(&re);
    }
    return 0;
}