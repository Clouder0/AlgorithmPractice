#include <cstdio>
#include <cstring>
#include <algorithm>
#include <ctype.h>
const int maxn = 5e6 + 100;
char s[maxn];
int main()
{
    scanf("%s",s + 1);
    int n = strlen(s + 1);
    long long t = 0;
    for (int i = 1; i <= n; ++i) t = t + s[i] - 48;
    if(t % 9 == 0) puts("Yes");
    else puts("No");
    return 0;
}