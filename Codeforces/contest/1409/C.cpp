#include <cstdio>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
#define DEBUG
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
const int maxn = 60;
int T,n,x,y,a[maxn];
int main()
{
    read(T);
    while(T--)
    {
        read(n), read(x), read(y);
        int res = 1 << 30;
        for (int i = 1; i < n; ++i)
            for (int j = i + 1; j <= n; ++j)
            {
                int dis = j - i;
                if ((y - x) % dis) continue;
                int d = (y - x) / dis;
                int a1=  x - (i - 1) * d;
                int an = y + (n - j) * d;
                if (a1 < 1 || an < 1) continue;
                int maxx = std::max(a1, an);
                if(res > maxx)
                {
                    a[1] = a1;
                    for (int i = 2; i <= n; ++i) a[i] = a[i - 1] + d;
                    res = maxx;
                }
            }
        std::swap(x,y);
        for (int i = 1; i < n; ++i)
            for (int j = i + 1; j <= n; ++j)
            {
                int dis = j - i;
                if ((y - x) % dis) continue;
                int d = (y - x) / dis;
                int a1 = x - (i - 1) * d;
                int an = y + (n - j) * d;
                if (a1 < 1 || an < 1) continue;
                int maxx = std::max(a1, an);
                if(res > maxx)
                {
                    a[1] = a1;
                    for(int i = 2;i<=n;++i) a[i] = a[i-1] + d;
                    res = maxx;
                }
            }
        for (int i = 1; i <= n; ++i) printf("%d ", a[i]);
        puts("");
    }
    return 0;
}