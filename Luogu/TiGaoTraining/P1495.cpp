#include <cstdio>
#define ll long long
const int maxn = 20;
int n, a[maxn], b[maxn];
inline void exgcd(ll a, ll b, ll& x, ll& y)
{
    if (b == 0) return (void)(x = 1, y = 0);
    exgcd(b, a % b, y, x), y -= (a / b) * x;
}
inline ll CRT()
{
    ll prod = 1,ans = 0;
    for (int i = 1; i <= n; ++i) prod *= a[i];
    for (int i = 1; i <= n; ++i)
    {
        ll x,y;
        exgcd(prod / a[i], a[i], x, y);
        ans = (ans + prod / a[i] * b[i] * x) % prod;
    }
    return (ans + prod) % prod;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d %d", a + i, b + i);
    printf("%lld\n", CRT());
    return 0;
}