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
const int maxn = 110;
int T, n, m, a[maxn][maxn], vis[maxn][maxn];
int main()
{
    read(T);
    while (T--)
    {
        read(n), read(m);
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j) read(a[i][j]);
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                if ((a[i][j] & 1) == ((i + j) & 1)) ++a[i][j];
        for (int i = 1; i <= n; puts(""), ++i)
            for (int j = 1; j <= m; ++j) printf("%d ", a[i][j]);
    }
    return 0;
}