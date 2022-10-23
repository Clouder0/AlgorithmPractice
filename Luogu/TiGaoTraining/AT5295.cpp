#include <cstdio>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
using std::max;
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
const int maxn = 2e6 + 100;
int r1, r2, c1, c2, prod[maxn], prodinv[maxn], inv[maxn], res;
inline int add(int x, int y) { int res = x + y; return res >= mod ? res - mod : res; }
inline int mul(int x, int y) { return 1ll * x * y % mod; }
inline int c(int n, int m) { return mul(prod[n], mul(prodinv[n - m], prodinv[m])); }
int main()
{
    read(r1), read(c1), read(r2), read(c2);
    inv[1] = 1;
    int up = r2 + c2 + 10;
    prod[0] = prodinv[0] = prod[1] = prodinv[1] = 1;
    for (int i = 2; i <= up; ++i)
        prod[i] = mul(prod[i - 1], i), prodinv[i] = mul(prodinv[i - 1], inv[i] = mul(inv[mod % i], mod - mod / i));
    for (int i = r1; i <= r2; ++i)
        res = add(res, add(c(i + c2 + 1, i + 1), mod - c(i + c1, i + 1)));
    printf("%d\n", res);
    return 0;
}