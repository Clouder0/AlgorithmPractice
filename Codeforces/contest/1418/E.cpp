#include <algorithm>
#include <cstdio>
const int mod = 998244353;
const int maxn = 2e5 + 100;
int n, m, d[maxn], sum[maxn];
void exgcd(int a, int b, int& x, int& y)
{
    if (!b) return (void)(x = 1, y = 0);
    exgcd(b, a % b, y, x), y -= (a / b) * x;
}
inline int inv(int x) { int k1, k2; exgcd(x, mod, k1, k2); return k1; }
int main()
{
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%d", d + i);
    std::sort(d + 1, d + 1 + n);
    for (int i = 1; i <= n; ++i) sum[i] = (sum[i - 1] + d[i]) % mod;
    for (int i = 1, a, b; i <= m; ++i)
    {
        scanf("%d %d", &a, &b);
        int l = 1, r = n, mid, ans = 0;
        while (l <= r)
        {
            mid = l + r >> 1;
            if (d[mid] < b) ans = mid, l = mid + 1;
            else r = mid - 1;
        }
        if (n - ans < a) { puts("0"); continue; }
        long long bres = (1ll * ((sum[n] - sum[ans] + mod) % mod) * ((mod + 1 - 1ll * a * inv(n - ans)) % mod)) % mod;
        long long sres = (1ll * (sum[ans] % mod) * ((mod + 1 - 1ll * a * inv(n - ans + 1)) % mod)) % mod;
        printf("%lld\n", (bres + sres + 2 * mod) % mod);
    }
    return 0;
}