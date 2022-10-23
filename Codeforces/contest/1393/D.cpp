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
const int maxn = 2100;
int n, m;
char a[maxn][maxn];
int up[maxn][maxn], down[maxn][maxn], h[maxn][maxn];
int L[maxn][maxn], R[maxn][maxn];
int main()
{
    read(n), read(m);
    for (int i = 1; i <= n; ++i) read(a[i] + 1);
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j)
    {
        up[i][j] = 1;
        if (a[i][j] == a[i - 1][j]) up[i][j] = up[i - 1][j] + 1;
    }
    for (int i = n; i; --i) for (int j = 1; j <= m; ++j)
    {
        down[i][j] = 1;
        if (a[i][j] == a[i + 1][j]) down[i][j] = down[i + 1][j] + 1;
    }
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) h[i][j] = std::min(up[i][j], down[i][j]);
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j)
    {
        L[i][j] = 1;
        if (a[i][j] == a[i][j - 1]) L[i][j] = std::min(L[i][j - 1] + 1, h[i][j]);
    }
    for (int i = 1; i <= n; ++i) for (int j = m; j; --j)
    {
        R[i][j] = 1;
        if (a[i][j] == a[i][j + 1]) R[i][j] = std::min(R[i][j + 1] + 1, h[i][j]);
    }
    long long ans = 0;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) ans += std::min(L[i][j], R[i][j]);
    printf("%lld\n", ans);
    return 0;
}