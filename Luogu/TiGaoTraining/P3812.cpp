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
const int maxn = 62;
int n;
long long a[maxn],s[maxn];
int main()
{
    read(n);
    for (int i = 1; i <= n; ++i) 
    {
        read(a[i]);
        for (int j = 60; j >= 0; --j)
            if (a[i] & (1ll << j))
            {
                if (!s[j]) { s[j] = a[i]; break; }
                a[i] ^= s[j];
            }
    }
    long long ans = 0;
    for (int i = 60; i >= 0; --i) if ((ans ^ s[i]) > ans) ans ^= s[i];
    printf("%lld\n",ans);
    return 0;
}