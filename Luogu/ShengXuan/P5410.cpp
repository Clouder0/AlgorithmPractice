#include <cstdio>
#include <cstring>
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
const int maxn = 2e7 + 100;
char a[maxn], b[maxn];
int n, m, z[maxn * 2];
int main()
{
    read(a), read(b);
    n = strlen(a), m = strlen(b);
    int l = 0, r = 0;
    z[0] = m;
    for (int i = 1; i < m; ++i)
    {
        if(i <= r)
        {
            if (z[i - l] < r - i + 1) z[i] = z[i - l];
            else for (z[i] = r - i + 1; i + z[i] < m && b[z[i]] == b[i + z[i]]; ++z[i]) ;
        }
        else for (; i + z[i] < m && b[z[i]] == b[i + z[i]]; ++z[i]) ;
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    long long res = 0, res2 = 0;
    for (int i = 0; i < m; ++i) res2 ^= 1ll * (i + 1) * (z[i] + 1);
    printf("%lld\n", res2);
    for (int i = m + 1; i < n + m + 1; ++i)
    {
        if(i <= r)
        {
            if(z[i - l] < r - i + 1) z[i] = z[i - l];
            else for(z[i] = r - i + 1;i + z[i] < n + m + 1 && b[z[i]] == a[i + z[i] - m - 1];++z[i]);
        }
        else for(;i + z[i] < n + m + 1 && b[z[i]] ==a[i + z[i] - m - 1];++z[i]);
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
        res ^= 1ll * (i - m) * (z[i] + 1);
    }
    printf("%lld\n", res);
    return 0;
}