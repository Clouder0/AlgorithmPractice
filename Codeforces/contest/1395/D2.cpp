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
int n,d,m;
int a[maxn];
long long sum[maxn];
int main()
{
    read(n),read(d),read(m);
    for (int i = 1; i <= n; ++i) read(a[i]);
    std::sort(a + 1,a + 1 + n);
    long long ans = a[n];
    --n;
    for (int i = 1; i <= n; ++i) sum[i] = sum[i-1] + a[i];
    int l = 1,r = n;
    while(l + d - 1 < r)
    {
        //[l,l+d-1] [r]
        if(a[r] <= m)
        {
            ans += sum[r] - sum[l-1];
            break;
        }
        else
        {
            if(sum[l+d-1] - sum[l-1] <= a[r]) ans += a[r--],l = l + d;
            else
            {
                while(l < r && a[l] <= m) ans += a[l++];
                while(l + d - 1 < r)
                {
                    ans += a[r--],l = l + d;
                }
                break;
            }
        }
    }
    printf("%lld\n",ans);
    return 0;
}