#include <cstdio>
#include <algorithm>
const int maxn = 4e5 + 100;
int n,a[maxn];
int f[maxn][60];
int main()
{
    scanf("%d",&n);
    for (int i = 1; i <= n; ++i) scanf("%d",a + i);
    for(int i = 1;i<=n;++i) f[i][a[i]] = i;
    int ans = 0;
    for (int j = 1; j <= 59; ++j)
        for (int i = 1; i <= n; ++i)
        {
        	if(f[i][j-1] && f[f[i][j-1] + 1][j-1]) f[i][j] = std::max(f[i][j],f[f[i][j - 1] + 1][j - 1]);
            if(f[i][j] > 0 && f[i][j] <= n) ans = j;
        }
    printf("%d\n",ans);
    return 0;
}