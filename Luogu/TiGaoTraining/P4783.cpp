#include <algorithm>
#include <cstdio>
const int maxn = 810;
const int p = 1e9 + 7;
#define ll long long
ll a[maxn][maxn];
int n;
void exgcd(ll a,ll b,ll &x,ll &y)
{
    if (b == 0) return (void)(x = 1, y = 0);
    exgcd(b, a % b, y, x), y -= (a / b) * x;
}
ll inv(ll x)
{
    ll k1,k2;
    exgcd(x,p,k1,k2);
    return ((k1 % p) + p) % p;
}
signed main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) scanf("%lld", &a[i][j]);
    for (int i = 1; i <= n; ++i) a[i][i + n] = 1;
    for (int i = 1; i <= n; ++i)
    {
        int maxx = i;
        for (int j = i + 1; j <= n; ++j) if (a[j][i] > a[maxx][i]) maxx = j;
        if (i != maxx) std::swap(a[i], a[maxx]);
        if (a[i][i] == 0) goto fail;
        ll tmp = inv(a[i][i]);//求逆元
        for (int j = 1; j <= n; ++j)
        {
            if (i == j) continue;
            ll frac = (a[j][i] * tmp) % p;  // a[j][i] / a[i][i]
            for (int k = i; k <= 2 * n; ++k)
                a[j][k] = (((a[j][k] - frac * a[i][k]) % p) + p) % p;//消元
        }
        for (int j = 1; j <= 2 * n; ++j) a[i][j] = (a[i][j] * tmp) % p;//处理为 1
    }
    for (int i = 1; i <= n; puts(""), ++i) for (int j = 1; j <= n; ++j) printf("%lld ", a[i][j + n]);
    return 0;
fail:
    puts("No Solution");
    return 0;
}