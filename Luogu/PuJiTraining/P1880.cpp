#include <cstdio>
#include <algorithm>
#include <cstring>
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
const int maxn = 210;
int n, a[maxn], sum[maxn], f[maxn][maxn], s[maxn][maxn];
int main()
{
    read(n);
    for (int i = 1; i <= n; ++i) read(a[i]), sum[i] = sum[i - 1] + a[i];
    for (int i = n + 1; i <= 2 * n; ++i) a[i] = a[i - n], sum[i] = sum[i - 1] + a[i];
    for (int i = 1; i <= n * 2; ++i) f[i][i] = 0, s[i][i] = i;
    for (int len = 2; len <= n; ++len)
        for (int i = 1, j = i + len - 1; j <= n * 2; ++i, ++j)
        {
            f[i][j] = 1 << 30;
            for (int k = s[i][j - 1]; k <= s[i + 1][j]; ++k)
                if (f[i][k] + f[k + 1][j] + sum[j] - sum[i - 1] < f[i][j])
                    f[i][j] = f[i][k] + f[k + 1][j] + sum[j] - sum[i - 1], s[i][j] = k;
        }
    int res = 1 << 30;
    for (int i = 1; i <= n; ++i) res = std::min(res, f[i][i + n - 1]);
    printf("%d\n", res);
    for (int i = 1; i <= n * 2; ++i) f[i][i] = 0, s[i][i] = i;
    for (int len = 2; len <= n; ++len)
        for (int i = 1, j = i + len - 1; j <= n * 2; ++i, ++j)
            f[i][j] = std::max(f[i][j - 1], f[i + 1][j]) + sum[j] - sum[i - 1];
    for (int i = 1; i <= n; ++i) res = std::max(res, f[i][i + n - 1]);
    printf("%d\n", res);
    return 0;
}