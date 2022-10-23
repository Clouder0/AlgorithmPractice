#include <algorithm>
#include <cstdio>
#include <ctype.h>
#define int long long
const int bufSize = 1e6;
inline char nc()
{
#ifdef DEBUG
    return getchar();
#endif
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
inline void read(char* s)
{
    static char c;
    for (; !isalpha(c); c = nc())
        ;
    for (; isalpha(c); c = nc()) *s++ = c;
    *s = '\0';
}
template <typename T>
inline T read(T& r)
{
    static char c;
    static int flag;
    flag = 1, r = 0;
    for (c = nc(); !isdigit(c); c = nc())
        if (c == '-') flag = -1;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r *= flag;
}
const int maxn = 4e5 + 100;
int n, p[maxn], pp[maxn];
int ld[maxn], rd[maxn], mld[maxn], mrd[maxn];
int sum[maxn];
void add(int m)
{
    if (m < n / 2)
    {
        // left [0,m] and [n-(n/2-m),n-1]
        // right [m, n-(n/2-m)-1]
        mld[m]++, ld[m] += m - n;
        if (n - 1 >= n - (n / 2 - m))
        {
            mld[n - 1]++, ld[n - 1] += m;
            mld[n - (n / 2 - m) - 1]--, ld[n - (n / 2 - m) - 1] -= m;
        }
        if (n - (n / 2 - m) - 1 >= m)
        {
            mrd[m]++, rd[m] += -m;
            mrd[n - (n / 2 - m)]--, rd[n - (n / 2 - m)] -= -m;
        }
    }
    else
    {
        // left [m-(n/2),m]
        // right [0, m-(n/2) - 1] and [m, n-1]
        mld[m]++, ld[m] += m - n;
        if (m - (n / 2) - 1 >= 0) mld[m - (n / 2) - 1]--, ld[m - (n / 2) - 1] -= m - n;
        mrd[m]++, rd[m] += -m;
        if (m - (n / 2) - 1 >= 0)
        {
            mrd[0]++, rd[0] += n - m;
            mrd[m - (n / 2)]--, rd[m - (n / 2)] -= n - m;
        }
    }
}
void calc()
{
    for (int i = 1; i <= n + 1; ++i) rd[i] += rd[i - 1], mrd[i] += mrd[i - 1];
    for (int i = n + 1; i >= 0; --i) ld[i] += ld[i + 1], mld[i] += mld[i + 1];
    for (int i = 0; i < n; ++i)
        sum[i] = ld[i] + rd[i] + i * mrd[i] + (n - i) * mld[i];
}
signed main()
{
    read(n);
    for (int i = 0; i < n; ++i) read(p[i]);
    for (int i = 0; i < n; ++i) add((i - p[i] + n) % n);
    calc();
    int res = 1ll << 60;
    for (int i = 0; i < n; ++i) res = std::min(res, sum[i]);
    printf("%lld\n", res);
    return 0;
}