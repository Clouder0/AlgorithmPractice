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
const int maxn = 110;
int T,n,a[maxn],b[maxn],c[maxn],d[maxn];
bool work()
{
    for(int i = 2;i<=n;++i)
    {
        if(a[i] != d[i-1]) d[i] = a[i];
        else if(b[i] != d[i-1]) d[i] = b[i];
        else if(c[i] != d[i-1]) d[i] = c[i];
    }
    return d[n] != d[1];
}
int main()
{
    read(T);
    while(T--)
    {
        read(n);
        for (int i = 1; i <= n; ++i) read(a[i]);
        for (int i = 1; i <= n; ++i) read(b[i]);
        for (int i = 1; i <= n; ++i) read(c[i]);
        d[1] = a[1];
        if(work()) goto yes;
        d[1] = b[1];
        if(work()) goto yes;
        d[1] = c[1];
        if(work()) goto yes;
        yes:
        for (int i = 1; i <= n; ++i) printf("%d ",d[i]);
        puts("");
    }
    return 0;
}