#include <cstdio>

const int maxn = 3e6 + 100;
namespace LinearInv
{
int n, p;
int inv[maxn];
void init()
{
    inv[1] = 1;
    for (int i = 2; i <= n; ++i) inv[i] = 1ll * (p - p / i) * inv[p % i] % p;
}
}  // namespace LinearInv

namespace ExgcdInv
{
int exgcd(int a, int b, int& x, int& y)
{
    if (b == 0)
    {
        x = 1, y = 0;
        return a;
    }
    int res = exgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return res;
}

int inv(int a, const int p)
{
    // ax \equiv 1 \pmod p \iff ax + py = 1
    int x, y;
    exgcd(a, p, x, y);
    x %= p;
    return x < 0 ? x + p : x;
}
}  // namespace ExgcdInv

namespace PowInv
{
int fastpow(int x, int k, const int p)
{
    int res = 1;
    for (; k > 0; k >>= 1)
    {
        if (k & 1) res = (1ll * res * x) % p;
        x = (1ll * x * x) % p;
    }
    return res;
}
int inv(int x, const int p)
{
    return fastpow(x, p - 2, p);
}
}  // namespace PowInv

namespace LinearAnyInv
{
int n, p, a[maxn], S[maxn], SV[maxn], invs[maxn];
void init()
{
    S[0] = 1;
    for (int i = 1; i <= n; ++i) S[i] = (1ll * S[i - 1] * a[i]) % p;
    SV[n] = ExgcdInv::inv(S[n], p);
    for (int i = n - 1; i; --i) SV[i] = (1ll * SV[i + 1] * a[i + 1]) % p;
    for (int i = 1; i <= n; ++i) invs[i] = (1ll * SV[i] * S[i - 1]) % p;
}
}  // namespace LinearAnyInv

int n, p;
int inv[maxn];
int main()
{
    scanf("%d %d", &n, &p);
    printf("%d\n", PowInv::inv(n, p));
    /*
    scanf("%d %d", &n, &p);
    LinearInv::n = n, LinearInv::p = p;
    LinearInv::init();
    for (int i = 1; i <= n; ++i) printf("%d\n", inv[i]);
    */
    return 0;
}