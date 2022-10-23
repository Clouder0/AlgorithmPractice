#include <cstdio>
#define ll long long
const int maxk = 20;
ll k, a[maxk], b[maxk];
void exgcd(ll a, ll b, ll& x, ll& y)
{
    if (b == 0) return (void)(x = 1, y = 0);
    exgcd(b, a % b, y, x), y -= (a / b) * x;
}
ll mul(ll a,ll b,ll mod)
{
    ll res = 0;
    while(a)
    {
        if(a & 1) res = (res + b) % mod;
        b = (b + b) % mod;
        a >>= 1;
    }
    return res % mod;
}
ll crt()
{
    ll prod = 1, ans = 0;
    for (int i = 1; i <= k; ++i) prod *= b[i];
    for (int i = 1; i <= k; ++i)
    {
        ll x, y, mi = prod / b[i];
        exgcd(mi, b[i], x, y);
        x = ((x % b[i]) + b[i]) % b[i];
        ans = (ans + mul(mul(mi, x, prod), a[i], prod)) % prod;
    }
    return (ans + prod) % prod;
}
int main()
{
    scanf("%lld",&k);
    for (int i = 1; i <= k; ++i) scanf("%lld",a+i);
    for (int i = 1; i <= k; ++i) scanf("%lld", b + i);
    printf("%lld\n", crt());
    return 0;
}