#include <cstdio>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
using std::abs;
using std::min;
#define DEBUG
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
int T, n, m, a[110][110],b[5],vis[110][110];
int main()
{
    read(T);
    while(T--)
    {
        read(n),read(m);
        for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) read(a[i][j]),vis[i][j] = 0;
        long long res = 0;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
            {
                if (i != n - i + 1 && j != m - j + 1 && !vis[i][j] && !vis[n - i + 1][j] && !vis[i][m - j + 1] && !vis[n - i + 1][m - j + 1])
                {
                    b[1] = a[i][j], b[2] = a[n - i + 1][j], b[3] = a[i][m - j + 1], b[4] = a[n - i + 1][m - j + 1];
                    vis[i][j] = vis[n - i + 1][j] = vis[i][m - j + 1] = vis[n - i + 1][m - j + 1] = 1;
                    std::sort(b + 1, b + 5);
                    res += 1ll * b[3] - b[2] + b[4] - b[1];
                }
                else if(i != n - i + 1 && !vis[i][j] && !vis[n - i + 1][j])
                {
                    b[1] = a[i][j], b[2] = a[n - i + 1][j];
                    std::sort(b + 1, b + 3);
                    res += 1ll * b[2] - b[1];
                    vis[i][j] = vis[n - i +1][j] = 1;
                }
                else if(j != m - j + 1 && !vis[i][j] && !vis[i][m - j + 1])
                {
                    b[1] = a[i][j],b[2] = a[i][m - j + 1];
                    std::sort(b + 1, b + 3);
                    res += 1ll * b[2] - b[1];
                    vis[i][j] = vis[i][m - j + 1] = 1;
                }
            }
        printf("%lld\n", res);
    }
    return 0;
}