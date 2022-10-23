#include <algorithm>
#include <cstdio>
#include <ctype.h>
#include <cstring>
using namespace std;
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
const int maxn = 110;
int n, k, v[maxn], t[maxn], sum;
long long maxsum;
long long f[maxn][5210][maxn];
inline bool check(int x){return x >= 2600 - sum * 2 && x <= 2600 + sum * 2;}
int main()
{
    read(n), read(k);
    for (int i = 1; i <= n; ++i) read(v[i]), read(t[i]), sum += t[i];
    for (int i = 0; i <= n; ++i)
        for (int j = 0; j <= 5200; ++j)
            for (int t = 0; t <= k; ++t) f[i][j][t] = -(1ll << 60);
    f[1][2600 + t[1]][0] = v[1];
    f[1][2600 + 2 * t[1]][1] = v[1];
    f[1][2600 - t[1]][0] = v[1];
    f[1][2600 - 2 * t[1]][1] = v[1];
    f[1][2600][0] = 0;
    for (int i = 2; i <= n; ++i)
    {
        for (int j = 2600 - sum * 2; j <= 2600 + sum * 2; ++j)
        {
            for (int p = 0; p <= k && p <= i; ++p)
            {
                f[i][j][p] = f[i - 1][j][p];
                if (check(j - t[i])) f[i][j][p] = max(f[i][j][p], f[i - 1][j - t[i]][p] + v[i]);
                if (check(j + t[i])) f[i][j][p] = max(f[i][j][p], f[i - 1][j + t[i]][p] + v[i]);
                if (p && check(j - 2 * t[i])) f[i][j][p] = max(f[i][j][p], f[i - 1][j - 2 * t[i]][p - 1] + v[i]);
                if (p && check(j + 2 * t[i])) f[i][j][p] = max(f[i][j][p], f[i - 1][j + 2 * t[i]][p - 1] + v[i]);
            }
        }
    }
    long long maxx = 0;
    for (int i = 0; i <= k; ++i) maxx = max(maxx, f[n][2600][i]);
    printf("%lld\n", maxx);
    // printf("%lld\n", dfs(1, 0, 0, 0));
    return 0;
}