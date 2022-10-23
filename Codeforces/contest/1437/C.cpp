#include <cstdio>
#include <algorithm>
#include <cstring>
#include <ctype.h>
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
int T, n, a[maxn];
int f[maxn][maxn * 2];
int main()
{
    read(T);
    while(T--)
    {
        read(n);
        memset(f, 0x3f, sizeof(f));
        f[0][0] = 0;
        int sum = 0;
        for (int i = 1; i <= n; ++i) read(a[i]);
        sort(a + 1, a + 1 + n);
        for (int i = 1; i <= n; ++i)
            for (int j = 0; j <= n * 2; ++j)
                for (int k = j - 1; k >= 0; --k)
                    f[i][j] = std::min(f[i][j], f[i - 1][k] + std::abs(a[i] - j));
        int minn = 1 << 30;
        for (int i = 0; i <= n  * 2; ++i) minn = std::min(f[n][i], minn);
        printf("%d\n", minn);
    }
    return 0;
}