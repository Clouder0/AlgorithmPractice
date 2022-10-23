#include <cstdio>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
#define int long long
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
int T, a, b;
signed main()
{
    read(T);
    while(T--)
    {
        read(a), read(b);
        int x = 0;
        for (int i = 32; i >= 0; --i)
        {
            int tx = x | (1ll << i);
            if((a ^ tx) + (b ^ tx) < (a ^ x) + (b ^ x)) x = tx;
        }
        printf("%lld\n",(a ^ x) + (b ^ x));
    }
    return 0;
}