#include <algorithm>
#include <cstdio>
#define ll long long
ll sx, sy, m, n, L;
inline ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }
inline void exgcd(ll a, ll b, ll& x, ll& y)
{
    if (b == 0) return (void)(x = 1, y = 0);
    exgcd(b, a % b, y, x), y -= (a / b) * x;
}
int main()
{
    scanf("%lld %lld %lld %lld %lld", &sx, &sy, &m, &n, &L);
    if(m - n < 0) std::swap(m,n),std::swap(sx,sy);
    ll g = gcd(m - n, L);
    ll a = m - n, b = L, x, y, c = sy - sx;
    if (c % g) { puts("Impossible"); return 0; }
    exgcd(a, b, x, y);
    x *= c / g, y *= c / g;
    ll mod = b / g;
    x = ((x % mod) + mod) % mod;
    printf("%lld\n", x);
    return 0;
}