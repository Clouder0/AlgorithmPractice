#include <algorithm>
#include <cstdio>
#include <ctype.h>
const int bufSize = 1e6;
#define DEBUG
inline char nc()
{
#ifdef DEBUG
    return getchar();
#endif
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
template <typename T>
inline T read(T& r)
{
    static char c;
    static int flag;
    flag = 1, r = 0;
    for (c = nc(); !isdigit(c); c = nc()) if (c == '-') flag = -1;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r *= flag;
}
const int mod = 998244353;
const int maxn = 2100;
int mul(int x, int y) { return 1ll * x * y % mod; }
int add(int x, int y) { int t = x + y; return t >= mod ? t - mod : t; }
void exgcd(int a, int b, int& x, int& y)
{
    if (!b) return (void)(x = 1, y = 0);
    exgcd(b, a % b, y, x), y -= (a / b) * x;
}
inline int inv(int x)
{
    int k1, k2;
    exgcd(x, mod, k1, k2);
    return (k1 %= mod) < 0 ? k1 + mod : k1;
}
int n, k, X[maxn], Y[maxn];
int main()
{
    read(n), read(k);
    for (int i = 1; i <= n; ++i) read(X[i]), read(Y[i]);
    int res = 0;
    for (int i = 1; i <= n; ++i)
    {
        int up = Y[i], down = 1;
        for (int j = 1; j <= n; ++j)
        {
            if (i == j) continue;
            up = mul(up, add(k, mod - X[j]));
            down = mul(down, add(X[i], mod - X[j]));
        }
        res = add(res, mul(up, inv(down)));
    }
    printf("%d\n", res);
    return 0;
}