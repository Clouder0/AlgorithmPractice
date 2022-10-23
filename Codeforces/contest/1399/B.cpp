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
const int maxn = 60;
int T,n;
int a[maxn],b[maxn];
int main()
{
    read(T);
    while(T--)
    {
        read(n);
        int mina = 1<<30,minb = 1<<30;
        for (int i = 1; i <= n; ++i) read(a[i]),mina = std::min(mina,a[i]);
        for (int i = 1; i <= n; ++i) read(b[i]),minb = std::min(minb,b[i]);
        long long ans = 0;
        for(int i = 1;i<=n;++i)
        {
            int needa = a[i] - mina,needb = b[i] - minb;
            ans += std::max(needa,needb);
        }
        printf("%lld\n",ans);
    }
    return 0;
}