#include <cstdio>
#include <algorithm>
using namespace std;
const long long inf = 1ll << 60;
const int maxn = 7200;
int T,n,a[maxn];
long long f[maxn][maxn];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for (int i = 1; i <= n; ++i) scanf("%d",a + i);
        for (int i = 1; i <= n; ++i) for (int j = i + 1; j <= n; ++j) f[j][i] = inf;
        for (int i = 1; i <= n; ++i) f[i][i] = 0;
        for (int r = 2; r <= n; ++r)
            for (int l = r - 1; l; --l)
                for (int k = l; k <= r; ++k)
                    f[r][l] = min(f[r][l], max(f[k][l], f[r][k + 1]) + a[k]);
        printf("%lld\n",f[n][1]);
    }
    return 0;
}