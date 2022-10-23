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
const int maxn = 1e5 + 100;
int T,n,a[maxn], cnt[100];
signed main()
{
    read(T);
    while(T--)
    {
        read(n);
        for (int i = 0; i < 32; ++i) cnt[i] = 0;
        for (int i = 1; i <= n; ++i) read(a[i]);
        for (int i = 1; i <= n; ++i)
            for (int j = 0; (1 << j) <= a[i]; ++j) cnt[j] += ((a[i] >> j) & 1);
//        for(int i = 0;i<32;++i) printf("%d %d\n",i,cnt[i]);
        for (int t = 1; t < 100000; ++t)
        {
            int flag = 1;
            for (int i = 32; i; --i)
            {
                if (cnt[i] > cnt[i - 1])
                {
                    int give = (cnt[i] - cnt[i - 1] + 2) / 3;
                    cnt[i] -= give, cnt[i - 1] += give * 2;
                    flag = 0;
                }
            }
            if (flag) break;
        }
        printf("%lld\n", cnt[0]);
    }
    return 0;
}