#include <cstdio>
using namespace std;
int s[1010],st;
int main()
{
    int num = 0;
    for(char c = getchar();c!='@';c=getchar())
    {
        if(c >= '0' && c <= '9')
            num = (num << 1) + (num << 3) + (c ^48);
        else if(c == '.')
            s[++st] = num,num = 0;
        else if(c == '+')
            s[st-1] = s[st] + s[st-1],--st;
        else if(c == '-')
            s[st-1] = s[st-1] - s[st],--st;
        else if(c == '*')
            s[st-1] = s[st-1] * s[st],--st;
        else if(c == '/')
            s[st-1] = s[st-1] / s[st],--st;
    }
    printf("%d",s[1]);
    return 0;
}