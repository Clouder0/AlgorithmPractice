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
const int maxn = 110;
int T,n,a[maxn];
int main()
{
    read(T);
    while(T--)
    {
        read(n);
        for (int i = 1; i <= n; ++i) read(a[i]);
        for (int i = 2; i <= n; i += 2)  printf("%d %d ",-a[i],a[i-1]);
        putchar('\n');
    }
    return 0;
}