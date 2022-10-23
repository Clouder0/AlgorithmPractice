#include <cstdio>
#include <algorithm>
#include <ctype.h>
char s[100][100];
int main()
{
    for (int i = 1; i <= 10; ++i) scanf("%s",s[i] + 1);
    int a = 0,b,c,d;
    for(int i = 1;i<=10;++i)
    {
        for (int j = 1; j <= 10; ++j)
            if (s[i][j] == '#')
            {
                a = i;
                goto end;
            }
    }
    end:
    for(int i = 10;i;--i)
    {
        for (int j = 1; j <= 10; ++j)
            if (s[i][j] == '#')
            {
                b = i;
                goto end2;
            }

    }
    end2:
    for(int i = 1;i<=10;++i) if(s[a][i] == '#') {c = i;break;}
    for (int i = 10; i; --i)
        if (s[a][i] == '#')
        {
            d = i;
            break;
        }
    printf("%d %d\n%d %d", a, b, c, d);
    return 0;
}