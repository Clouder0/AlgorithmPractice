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
const int maxn = 1100;
int n, m, a[maxn][maxn], mini[maxn], minj[maxn];
int main()
{
    read(n), read(m);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) read(a[i][j]);
    for (int i = 1; i <= n; ++i)
    {
        mini[i] = a[i][1];
        for (int j = 2; j <= m; ++j) mini[i] = std::min(mini[i], a[i][j]);
    }
    for (int j = 1; j <= m; ++j)
    {
        minj[j] = a[1][j];
        for (int i = 1; i <= n; ++i) minj[j] = std::min(minj[j], a[i][j]);
    }
    int res = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) res += (a[i][j] == mini[i] && a[i][j] == minj[j]);
    printf("%d\n", res);
    return 0;
}