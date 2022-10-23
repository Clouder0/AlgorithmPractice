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
int n;
int a[maxn];
int d[10];
int main()
{
    read(n);
    for (int i = 1; i <= n; ++i) read(a[i]);
    int ans = 0;
    for(int i = 1;i<=n;++i) for(int j = i + 1;j<=n;++j) for(int k = j + 1;k<=n;++k)
    {
        if(a[i] == a[j] || a[i] == a[k] || a[j] == a[k]) continue;
        d[1] = a[i],d[2] = a[j],d[3] = a[k];
        std::sort(d + 1,d + 1 + 3);
        if(d[1] + d[2] > d[3]) ++ans;
    }
    printf("%d\n",ans);
    return 0;
}