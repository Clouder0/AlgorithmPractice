#include <cstdio>
#include <algorithm>
#include <algorithm>
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
const int maxn = 2e3 + 100;
const int maxm = 2e6 + 100;
int n,m,a[maxn],b[maxn],c[maxn],d[maxn];
int minn[maxm];
int main()
{
    read(n),read(m);
    for (int i = 1; i <= n; ++i) read(a[i]),read(b[i]);
    for (int i = 1; i <= m; ++i) read(c[i]),read(d[i]);
    for (int i = 1; i <= n; ++i) 
        for (int j = 1; j <= m; ++j)
            if (c[j] >= a[i]) minn[c[j] - a[i]] = max(minn[c[j] - a[i]], d[j] - b[i] + 1);
    for (int i = 1000010; i >= 0; --i) minn[i] = max(minn[i], minn[i + 1]);
    int ans = 1<<30;
    for(int i = 0;i<=1000010;++i) ans = min(ans,i + minn[i]);
    printf("%d\n",ans);
    putchar('\65');
    return 0;
}