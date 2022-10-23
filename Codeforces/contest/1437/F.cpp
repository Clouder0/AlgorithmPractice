#include <cstdio>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
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
const int maxn = 5e3 + 100;
const int mod = 998244353;
int n, a[maxn], f[maxn], len[maxn], sum[maxn], prodinv[maxn], inv[maxn], prod[maxn];
inline int add(int x, int y)
{
    int res = x + y;
    return res >= mod ? res - mod : res;
}
inline int mul(int x, int y) { return 1ll * x * y % mod; }
inline void init()
{
    inv[1] = 1;
    for (int i = 2; i <= n; ++i) inv[i] = mul(inv[mod % i], mod - mod / i);
    prod[0] = prodinv[0] = 1;
    for (int i = 1; i <= n; ++i) prod[i] = mul(prod[i - 1], i), prodinv[i] = mul(prodinv[i - 1], inv[i]);
}
int main()
{
    read(n);
    for (int i = 1; i <= n; ++i) read(a[i]);
    std::sort(a + 1, a + 1 + n);
    init();
    if (a[n] < a[n - 1] * 2) { puts("0"); return 0; }
    f[0] = 1, sum[0] = prod[n - 1];
    int p = 1;
    for (int i = 1; i <= n; ++i)
    {
        while (a[p] * 2 <= a[i] && p <= n) ++p;
        --p;
        len[i] = p + 1;
        f[i] = add(f[i], mul(prodinv[n - len[i]], sum[p]));
        sum[i] = add(sum[i - 1], mul(f[i], prod[n - len[i] - 1]));
    }
    printf("%d\n", f[n]);
    return 0;
}