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
const int maxn = 1e5 + 100;
const int mod = 1e9 + 7;
inline int add(int x, int y) { int res = x + y; return res >= mod ? res - mod : res; }
inline int mul(int x, int y) { return 1ll * x * y % mod; }
int n, a[maxn], inv[maxn], sum[maxn], res, prod = 1;
int main()
{
    read(n);
    for (int i = 1; i <= n; ++i) read(a[i]);
    inv[1] = sum[1] = 1;
    for (int i = 2; i <= n; ++i) sum[i] = add(sum[i - 1], inv[i] = mul(inv[mod % i], mod - mod / i));
    for (int i = 1; i < n; ++i) prod = mul(prod, i), res = add(res, mul(a[i + 1] - a[i], sum[i]));
    printf("%d\n", mul(prod, res));
    return 0;
}