#include <cstdio>

const int maxn = 2e5 + 100;
int n;
char s[maxn];
int main()
{
    scanf("%d%s",&n,s + 1);
    int enclosing = 0;
    for (int i = 1; i <= n; ++i) 
    {
        if(s[i] == '"') enclosing ^= 1;
        if(!enclosing)
        {
            if(s[i] == ',') putchar('.');
            else putchar(s[i]);
        }
        else putchar(s[i]);
    }
    return 0;
}