#include <cstdio>
#include <cstring>
const int maxn = 1e6 + 10;
char s[maxn];
int n,ans,ansp;
int f[maxn];
int main()
{
    scanf("%s",s+1);
    n = strlen(s+1);
    for(int i = 1;i<=n;++i)
    {
        if(s[i] == '(' || s[i] == '[')
            continue;
        if((s[i] == ')' && s[i - f[i-1] - 1] == '(') || (s[i] == ']' && s[i - f[i-1] - 1] == '['))
            f[i] = f[i-1] + f[i - f[i-1] - 2] + 2;
        if(ans < f[i])
            ans = f[i],ansp = i;
    }
    for(int i = ansp - ans + 1;i<=ansp;++i)
        putchar(s[i]);
    return 0;
}