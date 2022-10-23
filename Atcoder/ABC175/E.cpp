#include <algorithm>
#include <cstdio>
#include <ctype.h>
#define DEBUG
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
    for (; !isalpha(c); c = nc());
    for (; isalpha(c); c = nc()) *s++ = c;
    *s = '\0';
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
const int maxn = 3100;
int n, m, num;
int a[maxn][maxn];
long long f[2][maxn][4], g[2][maxn];
int main()
{
    read(n), read(m), read(num);
    while (num--)
    {
        int x, y, z;
        read(x), read(y), read(z);
        a[x][y] = z;
    }
    int now = 1, last = 0;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            for (int k = 0; k <= 3; ++k)
            {
                f[now][j][k] = std::max(f[now][j - 1][k], f[last][j][k]);
                if (k)
                {
                    f[now][j][k] = std::max(f[now][j][k], g[last][j] + a[i][j]);
                    f[now][j][k] = std::max(f[now][j][k], f[now][j - 1][k - 1] + a[i][j]);
                }
            }
            g[now][j] = 0;
            for (int k = 0; k <= 3; ++k) g[now][j] = std::max(g[now][j], f[now][j][k]);
        }
        now ^= 1, last ^= 1;
    }
    printf("%lld\n", g[last][m]);
    return 0;
}