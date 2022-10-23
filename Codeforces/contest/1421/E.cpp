#include <cstdio>
#include <algorithm>
#include <cstring>
#include <ctype.h>
const int bufSize = 1e6;
using std::max;
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
const int maxn = 2e5 + 100;
int n, a[maxn];
long long f[maxn][3][2][2];
inline void gmax(long long &x, long long y) { if(y > x) x = y; }
int main()
{
    read(n);
    for (int i = 1; i <= n; ++i) read(a[i]);
    if(n == 1) {printf("%d\n",a[1]);return 0;}
    std::memset(f,~0x3f,sizeof(f));
    f[1][1][1][0] = a[1], f[1][2][0][0] = -a[1];
    for (int i = 1; i < n; ++i)
        for(int j = 0; j < 3;++j)
            for (int t = 0; t < 2; ++t)
                for (int now = 0; now < 2; ++now)
                {
                    gmax(f[i + 1][(j + 2) % 3][0][t | (now == 0)], f[i][j][now][t] - a[i + 1]);
                    gmax(f[i + 1][(j + 1) % 3][1][t | (now == 1)], f[i][j][now][t] + a[i + 1]);
                }
    printf("%lld\n",max(f[n][1][0][1],f[n][1][1][1]));
    return 0;
}