#include <algorithm>
#include <cstdio>
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
const int maxn = 2e5 + 100;
int n, k, a[maxn], zeromid;
int check(long long mid)
{
    int p = zeromid, res = 0;
    for (int i = 1; i < zeromid; ++i)
    {
        while (1ll * a[i] * a[p] > mid && p <= n) ++p;
        if (p <= n) res += (n - p + 1);
    }
    p = n;
    for (int i = zeromid; i <= n; ++i)
    {
        while (1ll * a[i] * a[p] > mid && p > 0) --p;
        if (p > i) res += p - i;
    }
    p = 1;
    for (int i = zeromid - 1; i > 0; --i)
    {
        while (1ll * a[i] * a[p] > mid && p < zeromid) ++p;
        if (p < i) res += i - p;
    }
    return res;
}
template <typename T>
inline T abs(const T& x)
{
    return x > 0 ? x : -x;
}
signed main()
{
    read(n), read(k);
    for (int i = 1; i <= n; ++i) read(a[i]);
    std::sort(a + 1, a + 1 + n);
    int maxx = std::max(abs(a[n]), abs(a[1]));
    long long l = -(maxx * maxx), r = maxx * maxx, mid, ans = 0;
    for (int i = 1; !zeromid && i <= n; ++i) if (a[i] >= 0) zeromid = i;
    while (l <= r)
    {
        mid = (l + r) >> 1;
        if (check(mid) >= k) ans = mid, r = mid - 1;
        else l = mid + 1;
    }
    printf("%lld\n", ans);
    return 0;
}