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
const int mod = 1e9 + 7;
const int maxn = 1e5 + 100;
int n, x, pos;
signed main()
{
    read(n), read(x), read(pos);
    int l = 0, r = n, mid, big = 0, small = 0;//small : <= x big: > x
    while (l < r)
    {
        mid = (l + r) / 2;
        if (pos >= mid) l = mid + 1, small += (mid < pos);
        else r = mid, ++big;
    }
    if (small >= x || big > n - x) { puts("0"); return 0; }
    // A(x,small) * A(n - x,big) * A(n - big - small,n - big - small)
    int res = 1; 
    for (int i = 0; i < small; ++i) res = (1ll * res * (x - 1 - i)) % mod;
    for (int i = 0; i < big; ++i) res = (1ll * res * (n - x - i)) % mod;
    int rest = n - big - small - 1;
    for (int i = 1; i <= rest; ++i) res = (1ll * res * i) % mod;
    printf("%lld\n", res);
    return 0;
}