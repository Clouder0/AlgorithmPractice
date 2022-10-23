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
const int mod = 1e9 + 7;
const int maxn = 2e5 + 100;
inline int add(int x, int y) { int res = x + y; return res >= mod ? res - mod : res; }
inline int mul(int x, int y) { return 1ll * x * y % mod; }
int n, k, prod[maxn], inv[maxn], prodinv[maxn], res;
inline int C(int n, int m) { return mul(prod[n], mul(prodinv[n - m], prodinv[m])); }
int main()
{
    read(n), read(k);
    if(k >= n) k = n - 1;
    prod[0] = prodinv[0] = prod[1] = prodinv[1] = inv[1] = 1;
    for (int i = 2; i <= n; ++i) prod[i] = mul(prod[i - 1], i), prodinv[i] = mul(prodinv[i - 1], inv[i] = mul(inv[mod % i], mod - mod / i));
    for (int i = 0; i <= k; ++i) res = add(res, mul(C(n, i), C(n - 1, n - i - 1)));
    printf("%d\n", res);
    return 0;
}