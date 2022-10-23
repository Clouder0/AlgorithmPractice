#include <cstdio>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
#define int long long
inline char nc()
{
    #ifdef DEBUG
    return getchar();
    #endif
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
template<typename T>
inline T read(T &r)
{
    static char c;
    static int flag;
    flag = 1, r = 0;
    for (c = nc(); !isdigit(c); c = nc()) if (c == '-') flag = -1;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r *= flag;
}
const int maxn = 3e5 + 100;
const int mod = 998244353;
int n, a[maxn];
inline int add(int x, int y)
{
    x %= mod, y %= mod;
    int res = x + y;
    return res >= mod ? res - mod : res;
}
inline int mul(int x, int y) { return 1ll * x * y % mod; }
void exgcd(int a, int b, int& x, int& y)
{
    if (b == 0) return (void)(x = 1, y = 0);
    exgcd(b, a % b, y, x), y -= (a / b) * x;
}
int inv(int x)
{
    int k1, k2;
    exgcd(x, mod, k1, k2);
    k1 = (k1 % mod + mod) % mod;
    return k1;
}
signed main()
{
    read(n);
    for (int i = 1; i <= 2 * n; ++i) read(a[i]);
    std::sort(a + 1, a + 1 + n * 2);
    int sum1 = 0, sum2 = 0;
    for (int i = 1; i <= n; ++i) sum1 = add(sum1, a[i]);
    for (int i = n + 1; i <= 2 * n; ++i) sum2 = add(sum2, a[i]);
    int sum = add(sum2, mod - sum1);
    int up = 1;
    for (int i = 0; i < n; ++i) up = mul(up, 2 * n - i);
    int down = 1;
    for (int i = 1; i <= n; ++i) down = mul(down, i);
    down = inv(down);
    int c = mul(up, down);
    printf("%lld\n", mul(sum, c));
    return 0;
}