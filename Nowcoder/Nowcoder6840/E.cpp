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
const int maxm = 1e4 + 100;
const int maxn = 110;
int n,m;
int f[maxm];
int w[maxn],v[maxn];
int main()
{
    read(n),read(m);
    for (int i = 1; i <= n; ++i) read(w[i]),read(v[i]);
    for (int i = 1; i <= n; ++i) 
    {
        for(int j = m;j>=w[i];--j)
            f[j] = std::max(f[j],f[j-w[i]] + v[i]);
    }
    int ans = 0;
    for(int i = 0;i<=m;++i) ans = std::max(ans,f[i]);
    printf("%d\n",ans);
    return 0;
}