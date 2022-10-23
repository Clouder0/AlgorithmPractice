#include <cstdio>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
using namespace std;
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
const int maxn = 40;
int n,a[maxn][maxn];
int main()
{
    while(scanf("%d",&n) && n != 0)
    {
        for (int i = 1; i <= n; ++i) for (int j = i + 1; j <= n; ++j) scanf("%d", a[i] + j), a[j][i] = a[i][j];
        int ans = a[1][2];
        for (int i = 3; i <= n; ++i)
        {
            int minn = 1 << 30;
            for (int j = 2; j < i; ++j) minn = min(minn, (a[1][i] + a[j][i] - a[1][j]) / 2);
            ans += minn;
        }
        printf("%d\n",ans);
    }
    return 0;
}