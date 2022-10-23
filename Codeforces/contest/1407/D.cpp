#include <cstdio>
#include <cstring>
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
const int maxn = 5e5 + 100;
int n,a[maxn];
int lasmax[maxn],lasmin[maxn],nexmax[maxn],nexmin[maxn],st[maxn],top;
int f[maxn];
int main()
{
    memset(f,0x3f,sizeof(f));
    read(n);
    for (int i = 1; i <= n; ++i) read(a[i]);
    for (int i = 1; i <= n; ++i) 
    {
        while(top && a[st[top]] <= a[i]) nexmax[st[top--]] = i;
        st[++top] = i;
    }
    while(top) nexmax[st[top--]] = n + 1;
    for (int i = 1; i <= n; ++i) 
    {
        while(top && a[st[top]] >= a[i]) nexmin[st[top--]] = i;
        st[++top] = i;
    }
    while(top) nexmin[st[top--]] = n + 1;
    for (int i = n; i; --i) 
    {
        while(top && a[st[top]] <= a[i]) lasmax[st[top--]] = i;
        st[++top] = i;
    }
    while(top) lasmax[st[top--]] = 0;
    for (int i = n; i; --i) 
    {
        while(top && a[st[top]] >= a[i]) lasmin[st[top--]] = i;
        st[++top] = i;
    }
    while(top) lasmin[st[top--]] = 0;
    f[1] = 0;
    for (int i = 1; i <= n; ++i) 
    {
        f[i] = std::min(f[i],f[lasmax[i]] + 1);
        f[i] = std::min(f[i],f[lasmin[i]] + 1);
        f[nexmax[i]] = std::min(f[nexmax[i]],f[i] + 1);
        f[nexmin[i]] = std::min(f[nexmin[i]],f[i] + 1);
        f[i + 1] = std::min(f[i + 1], f[i] + 1);
    }
    printf("%d\n",f[n]);
    return 0;
}