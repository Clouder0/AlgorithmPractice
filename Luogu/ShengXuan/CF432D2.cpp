#include <cstdio>
#include <cstring>
#include <algorithm>
const int maxn = 1e5 + 100;
char s[maxn];
int n, z[maxn], num[maxn], totalnum;
int main()
{
    scanf("%s",s + 1);
    n = strlen(s + 1);
    int l = 0,r = 0;
    for (int i = 2; i <= n; ++i)
    {
        if (i > r) for (; i + z[i] <= n && s[i + z[i]] == s[z[i] + 1];) ++z[i];
        else 
        {
            if(z[i - l + 1] < r - i + 1) z[i] = z[i - l + 1] ;
            else for(z[i] = r - i + 1;i + z[i] <= n && s[i + z[i]] == s[z[i] + 1];) ++z[i];
        }
        if(i + z[i] - 1 > r) l = i,r = i + z[i] - 1;
        num[z[i]]++;
    }
    z[1] = n;
    for (int i = n; i; --i) num[i] += num[i + 1];
    for(int i = 1;i<=n;++i) num[i]++;
    for (int i = 1; i <= n; ++i) if (z[i] == n - i + 1) ++totalnum; else num[n - i + 1] = 0;
    printf("%d\n", totalnum);
    for (int i = 1; i <= n; ++i) if (num[i] > 0) printf("%d %d\n", i, num[i]);
    return 0;
}