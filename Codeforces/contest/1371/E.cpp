#include <cstdio>
#include <algorithm>
#include <ctype.h>
template <typename T>
inline T max(const T &a, const T &b) { return a > b ? a : b; }
template <typename T>
inline T min(const T &a, const T &b) { return a < b ? a : b; }
const int bufSize = 1e6;
inline char nc()
{
#ifdef DEBUG
    return getchar();
#endif
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
template <typename T>
inline T read(T &r)
{
    static char c;
    r = 0;
    for (c = nc(); !isdigit(c);)
        c = nc();
    for (; isdigit(c); c = nc())
        r = r * 10 + c - 48;
    return r;
}
const int maxn = 5100;
int cnt[maxn], a[maxn], ans[maxn], tot;
int n, p;
int main()
{
    read(n), read(p);
    for (int i = 1; i <= n; ++i)
        read(a[i]), cnt[a[i]]++;
    std::sort(a + 1, a + 1 + n);
    int start = max(0, a[n] - n + 1);
    for (int i = 1; i <= a[n] + n; ++i)
        cnt[i] += cnt[i - 1];
    for (int x = start; x <= a[n]; ++x)
    {
        for (int i = 0; i < n; ++i)
            if ((cnt[i + x] - i) % p == 0)
                goto NO;
        ans[++tot] = x;
    NO:;
    }
    printf("%d\n", tot);
    for (int i = 1; i <= tot; ++i)
        printf("%d ", ans[i]);
    return 0;
}