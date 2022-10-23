#include <cstdio>
#include <algorithm>
using namespace std;
const long long inf = 1ll << 60;
const int maxn = 7200;
int T,n,a[maxn];
long long f[maxn][maxn];
int q[maxn],qt,qh;
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for (int i = 1; i <= n; ++i) scanf("%d",a + i);
        for (int i = 1; i <= n; ++i) for (int j = i + 1; j <= n; ++j) f[j][i] = inf;
        for (int r = 2; r <= n; ++r)
        {
            qh = qt = 1, q[1] = r - 1, f[r][r - 1] = a[r - 1];
            for (int l = r - 2, p = r; l > 0; --l)
            {
                while (p > l && f[p - 1][l] > f[r][p]) --p;
                //x in [l,p - 1] f[l][x] <= f[x + 1][r]
                //x in [p,r] f[l][x] > f[x + 1][r]
                //l <-,p <-
                f[r][l] = a[p] + f[p][l];
                while (qt >= qh && q[qh] >= p) ++qh;//should in [l,p - 1]
                if (qt >= qh) f[r][l] = min(f[r][l], f[r][q[qh] + 1] + a[q[qh]]);
                while (qt >= qh && f[r][q[qt] + 1] + a[q[qt]] >= f[r][l + 1] + a[l]) --qt;
                q[++qt] = l;
            }
        }
        printf("%lld\n",f[n][1]);
    }
    return 0;
}