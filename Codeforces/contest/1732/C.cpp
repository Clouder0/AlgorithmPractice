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
const int maxn = 1e5 + 100;
int T, n, q, a[maxn], L[maxn], R[maxn];
long long sum[maxn], pre[maxn];
int main()
{
    read(T);
    while(T--)
    {
        read(n), read(q);
        for (int i = 1; i <= n; ++i) read(a[i]);
        int x,y;
        read(x),read(y);
        sum[0] = pre[0] = 0;
        for (int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + a[i], pre[i] = pre[i - 1] ^ a[i];
        long long res = sum[n] - pre[n];
//        for(int i = 1;i<=n;++i) printf("%lld ",sum[i]);
//        puts("sum");
//        for(int i = 1;i<=n;++i) printf("%lld ",pre[i]);
//        puts("pre");
        int l = 1, r = n, mid, ans, ansl, ansr;
        while (l <= r)
        {
            mid = (l + r) >> 1;
            int flag = 0;
            for (int i = mid; !flag && i <= n; ++i)
            {
                long long now = sum[i] - sum[i - mid] - (pre[i] ^ pre[i - mid]);
//                printf("[%d %d] %lld\n",i - mid + 1,i,now);
                if (now == res) flag = 1, ansl = i - mid + 1, ansr = i;
            }
            if (flag)
                ans = mid, r = mid - 1;
            else
                l = mid + 1;
        }
        printf("%d %d\n", ansl, ansr);
//        puts("");
    }
    return 0;
}