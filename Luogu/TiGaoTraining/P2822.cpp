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
inline void read(char *s)
{
    static char c;
    for (; !isalpha(c); c = nc());
    for (; isalpha(c); c = nc()) *s++ = c;
    *s = '\0';
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
const int maxn = 2100;
int t,k;
int C[maxn][maxn],sum[maxn][maxn];
int main()
{
    read(t), read(k);
    C[0][0] = 1;
    for (int i = 1; i <= 2000; ++i)
    {
        C[i][0] = 1;
        for (int j = 1; j <= i; ++j)
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % k, sum[i][j] = (C[i][j] == 0);
    }
    for (int i = 1; i <= 2000; ++i) for (int j = 1; j <= 2000; ++j) sum[i][j] += sum[i - 1][j];
    for (int i = 1; i <= 2000; ++i) for (int j = 1; j <= 2000; ++j) sum[i][j] += sum[i][j - 1];
    for (int i = 1, n, m; i <= t; ++i) read(n), read(m), printf("%d\n", sum[n][std::min(n, m)]);
    return 0;
}