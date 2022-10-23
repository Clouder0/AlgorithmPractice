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
int gcd(int x, int y) { return y == 0 ? x : gcd(y, x % y); }
const int maxn = 1e3 + 100;
int T, n, a[maxn], used[maxn], b[maxn], c[maxn];
int main()
{
    read(T);
    while (T--)
    {
        read(n);
        for (int i = 1; i <= n; ++i) read(a[i]), used[i] = 0;
        int maxi = 1;
        for (int i = 2; i <= n; ++i) if (a[maxi] < a[i]) maxi = i;
        used[maxi] = 1, b[1] = c[1] = a[maxi];
        for (int i = 2; i <= n; ++i)
        {
            int maxx = 0, maxj = 0;
            for (int j = 1; j <= n; ++j)
            {
                if (used[j]) continue;
                int t = gcd(b[i - 1], a[j]);
                if (t > maxx) maxx = t, maxj = j;
            }
            used[maxj] = 1, b[i] = maxx, c[i] = a[maxj];
        }
        for (int i = 1; i <= n; ++i) printf("%d ", c[i]);
        puts("");
    }
    return 0;
}