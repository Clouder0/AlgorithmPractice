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
const int maxn = 1e4 + 100;
int T, n, f[maxn];
int main()
{
    for (int i = 1; i <= 10000; ++i)
    {
        int x = i, t = x % 10, flag = 1, sum = 0;
        while (x) flag &= ((x % 10) == t), sum++, x /= 10;
        if (flag) f[i] = sum;
    }
    read(T);
    while(T--)
    {
        read(n);
        int x = n % 10;
        int res = 0;
        for (int i = 1; i < x; ++i)
        {
            int t = i;
            while (t < 10000) res += f[t], t = t * 10 + i;
        }
        int t = x;
        while(t <= n) res += f[t],t = t * 10 + x;
        printf("%d\n",res);
    }
    return 0;
}