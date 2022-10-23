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
const int maxn = 100;
int T,n,a[maxn];
int main()
{
    read(T);
    while(T--)
    {
        read(n);
        for (int i = 1; i <= n; ++i) read(a[i]);
        int l = 0,r = 0;
        for (int i = 1; !l && i <= n; ++i) if (a[i]) l = i;
        for (int i = n; !r && i; --i) if (a[i]) r = i;
        int res = 0;
        for(int i = l;i<=r;++i) res += !a[i];
        printf("%d\n",res);
    }
    return 0;
}