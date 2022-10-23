#include <algorithm>
#include <cstdio>
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
const int inf = 1 << 30;
int n, m, a[maxn], b[maxn], sum;
int num[maxn];
int f[2][maxn], now, last;
int q[maxn], qt, qh, id[maxn];
int main()
{
    read(n), read(m);
    for (int i = 1; i <= n; ++i) read(a[i]), read(b[i]), sum += a[i], ++num[b[i] - a[i] + m];
    now = 0, last = 1;
    for (int i = 0; i <= m; ++i) f[last][i] = inf;
    f[last][sum] = 0;
    for (int t = 0; t <= 2 * m; ++t)
    {
        if (num[t] == 0) continue;
        int w = t - m;
        if (w == 0) continue;
        if (w > 0)
        {
            for (int j = 0; j < w; ++j)
            {
                qh = 1, qt = 0;
                for (int k = 0; j + k * w <= m; ++k)
                {
                    while (qt >= qh && k - id[qh] > num[t]) ++qh;
                    int ins = f[last][j + k * w] - k;
                    while (qt >= qh && q[qh] >= ins) ++qh;
                    q[++qt] = ins, id[qt] = k;
                    f[now][j + k * w] = q[qh] + k;
                }
            }
        }
        else
        {
            w = -w;
            for (int j = 0; j < w; ++j)
            {
                qh = 1, qt = 0;
                for (int k = 0; m - j - k * w >= 0; ++k)
                {
                    while (qt >= qh && k - id[qh] > num[t]) ++qh;
                    int ins = f[last][m - j - k * w] - k;
                    while (qt >= qh && q[qh] >= ins) ++qh;
                    q[++qt] = ins, id[qt] = k;
                    f[now][m - j - k * w] = q[qh] + k;
                }
            }
        }
        now ^= 1, last ^= 1;
    }
    for (int i = 0; i <= m; ++i)
        if (f[last][i] >= inf)
            puts("-1");
        else
            printf("%d\n", f[last][i]);
    return 0;
}