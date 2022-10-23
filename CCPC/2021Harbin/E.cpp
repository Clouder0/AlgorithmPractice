#include <cstdio>
#include <algorithm>
#include <ctype.h>
#define int long long
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
const int maxn = 1e5 + 10;
int T, n, a[maxn];
signed main()
{
    read(T);
    while(T--)
    {
        read(n);
        for (int i = 1; i <= n; ++i) read(a[i]);
        long long M, now;
        for (int i = 1; i <= n; ++i)
        {
            if (a[i] > (1ll << (i - 1))) goto no;
            if (a[i] != (1ll << (i - 1)))
            {
                M = (1ll << (i - 1)) - a[i];
                if(a[i] >= M) goto no;
                now = a[i];
                for (int j = i + 1; j <= n; ++j)
                {
                    now = (now * 2) % M;
                    if (now != a[j]) goto no;
                }
                printf("%lld\n", M);
                goto yes;
            }
        }
        goto no;
    yes:
        continue;
    no:
        puts("-1");
        continue;
    }
    return 0;
}