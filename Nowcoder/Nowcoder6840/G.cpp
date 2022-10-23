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
int T;
int n,m;
int main()
{
    read(T);
    while(T--)
    {
        read(n),read(m);
        n -= m;//n女m男
        long long ans = 0;
        if((m & 1) == 0)
        {
            ans += 1ll * (2 + m) * (m / 2) / 2;
            ans += (n + 1) / 2;
            printf("%lld\n",ans);
        }
        else
        {
            ans += 1ll * (m + 3) * (m / 2) / 2;
            ++n;
            ans += (n + 1) / 2;
            printf("%lld\n",ans);
        }
    }
    return 0;
}