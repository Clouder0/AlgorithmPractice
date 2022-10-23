#include <cstdio>
#include <algorithm>
#include <ctype.h>
const int maxn = 1e5 + 10;
int n;
char s[maxn];
int main()
{
    scanf("%d%s",&n,s + 1);
    int flag = 1;
    for(int i = 1;i<=n;++i) if(s[i] == '0') flag = 0;
    if(flag) puts("0");
    else puts((s[1] == '1' || s[n] == '1') ? "1" : "2");
    return 0;
}