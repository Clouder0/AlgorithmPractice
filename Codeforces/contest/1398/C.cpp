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
    for (; !isdigit(c); c = nc());
    for (; isdigit(c); c = nc()) *s++ = c;
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
const int maxn = 1e6 + 100;
int T,n,sum[maxn],cnt[2 * maxn];
char s[maxn];
int main()
{
    read(T);
    while(T--)
    {
        read(n);
        read(s + 1);
        for (int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + s[i] - 48;
        for (int i = 1; i <= n; ++i) cnt[sum[i] - i + maxn] = 0;
        long long ans = 0;
        cnt[0 + maxn] = 1;
        for (int i = 1; i <= n; ++i)
        {
            ans += cnt[sum[i] - i + maxn];
            cnt[sum[i] - i + maxn]++;
        }
        printf("%lld\n", ans);
    }
    return 0;
}