#include <cstdio>
#include <cstring>
#include <algorithm>
#include <ctype.h>
using namespace std;
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
const int maxn = 80;
int n, m, p, a[maxn][maxn];
int f[maxn][maxn], g[maxn], dp[2][maxn];
int main()
{
    read(n), read(m), read(p);
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) read(a[i][j]);
    int now = 1, last = 0;
    memset(dp, ~0x3f, sizeof(dp));
    dp[last][0] = dp[now][0] = 0;
    for (int i = 1; i <= n; ++i)
    {
        memset(f, ~0x3f, sizeof(f)), memset(g, ~0x3f, sizeof(g)), memset(dp[now], ~0x3f, sizeof(dp[now]));
        f[0][0] = 0;
        for (int j = 1; j <= m; ++j)
            for (int k = m / 2; k; --k)
                for (int t = 0; t <= p; ++t)
                    f[k][(t + a[i][j]) % p] = std::max(f[k][(t + a[i][j]) % p], f[k - 1][t] + a[i][j]);
       for (int ex = 0; ex <= p; ++ex)
            for (int k = 0; k <= m / 2; ++k)
                g[ex] = std::max(g[ex], f[k][ex]);
        for (int j = 0; j <= p; ++j)
            for (int k = 0; k <= p; ++k)
                dp[now][(j + k) % p] = std::max(dp[now][(j + k) % p], dp[last][j] + g[k]);
        now ^= 1, last ^= 1;
    }
    printf("%d\n", dp[last][0]);
    return 0;
}