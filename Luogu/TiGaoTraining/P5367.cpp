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
const int mod = 998244353;
const int maxn = 1e6 + 100;
int n, a[maxn], prod[maxn], sum[maxn];
inline int mul(int a, int b) { return 1ll * a * b % mod; }
inline int add(int a, int b)
{
    int res = a + b;
    return res >= mod ? res - mod : res;
}
namespace Bit
{
inline void add(int x, int k) { for (; x <= n; x += x & -x) sum[x] += k; }
inline int ask(int x) { int res = 0; for (; x > 0; x -= x & -x) res += sum[x]; return res; }
}  // namespace Bit
int main()
{
    read(n);
    for (int i = 1; i <= n; ++i) read(a[i]);
    prod[0] = 1;
    for (int i = 1; i <= n; ++i) prod[i] = mul(prod[i - 1], i);
    int res = 0;
    for (int i = n; i; --i)
    {
        int t = Bit::ask(a[i]);
        res = add(res, mul(t, prod[n - i]));
        Bit::add(a[i], 1);
    }
    printf("%d\n", add(1, res));
    return 0;
}