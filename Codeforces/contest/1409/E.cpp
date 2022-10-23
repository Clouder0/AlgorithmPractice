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
const int maxn = 2e5 + 100;
int T,n,k;
int X[maxn];
int f[maxn],g[maxn];
int main()
{
    read(T);
    while(T--)
    {
        read(n),read(k);
        for (int i = 1; i <= n; ++i) read(X[i]);
        for (int i = 1, x; i <= n; ++i) read(x);
        std::sort(X + 1,X + 1 + n);
        for (int i = 1; i <= n; ++i)
        {
            int R = X[i] + k;
            int l = i, r = n, mid, ans = 0;
            while (l <= r)
            {
                mid = l + r >> 1;
                if(X[mid] <= R) ans = mid,l = mid + 1;
                else r = mid - 1;
            }
            f[i] = ans - i + 1;
        }
        for (int i = 1; i <= n; ++i) 
        {
            int L = X[i] - k;
            int l = 1, r = i, mid, ans = 0;
            while(l <= r)
            {
                mid = l + r >> 1;
                if (X[mid] >= L) ans = mid, r = mid - 1;
                else l = mid + 1;
            }
            g[i] = std::max(g[i - 1], i - ans + 1);
        }
        int ans = 0;
        for (int i = 1; i <= n; ++i) ans = std::max(ans, g[i - 1] + f[i]);
        printf("%d\n",ans);
    }
    return 0;
}