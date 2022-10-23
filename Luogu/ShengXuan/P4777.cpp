#include <cstdio>
#define ll long long
const int maxn = 1e6 + 100;
int n;
ll p[maxn], r[maxn];
ll exgcd(ll a, ll b, ll& x, ll& y)
{
    if (b == 0)
    {
        x = 1, y = 0;
        return a;
    }
    ll g = exgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return g;
}
ll mul(ll a, ll b, ll mod)
{
    ll res = 0;
    while (b > 0)
    {
        if (b & 1) res = (res + a) % mod;
        a = (a + a) % mod;
        b >>= 1;
    }
    return ((res % mod) + mod) % mod;
}
inline ll exCRT()
{
    ll lcm = p[1], lastr = r[1], k1, k2;
    for (int i = 2; i <= n; ++i)
    {
        ll a = lcm, b = p[i], c = (((r[i] - lastr) % p[i]) + p[i]) % p[i];
        ll g = exgcd(a, b, k1, k2);
        ll mod = p[i] / g;
        k1 = ((k1 % mod) + mod) % mod;
        k1 = mul(k1, c / g, mod);

        lastr += k1 * lcm;
        lcm = lcm / g * p[i];
        lastr = ((lastr % lcm) + lcm) % lcm;
    }
    return lastr;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%lld %lld", p + i, r + i);
    printf("%lld\n", exCRT());
    return 0;
}