#include <cstdio>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
using namespace std;
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
const int maxn = 2e5 + 100;
int T,n,k;
long long l1,r1,l2,r2;
int main()
{
    read(T);
    while(T--)
    {
        read(n),read(k),read(l1),read(r1),read(l2),read(r2);
        long long x = max(min(r1,r2) - max(l1,l2),0ll);
        if (n * x >= k) { puts("0"); continue; }
        k -= n * x;
        long long rest = max(r1,r2) - min(l1,l2) - x;
        long long need = max(max(l1,l2) - min(r1,r2),0ll);
        long long ans = 1ll<<60;
        for(int i = 1;i<=n;++i)
        {
            if (rest * i >= k) ans = min(ans, i * need + k);
            else ans = min(ans, i * (need + rest) + (k - rest * i) * 2);
        }
        printf("%lld\n",ans);
    }
    return 0;
}