#include <cstdio>
#include <algorithm>
#include <ctype.h>
#include <cstring>
const int bufSize = 1e6;
#define DEBUG
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
const int maxn = 1e5 + 100;
const int mod = 1e9 + 7;
const int inv = 700000005;
char s[maxn];
int n, f[maxn], g[maxn], k[maxn];
inline int add(int x, int y)
{
    int t = x + y;
    if (t >= mod) return t - mod;
    return t;
}
inline int mul(int x, int y) { return (1ll * x * y) % mod; }
int main()
{
    read(s + 1);
    n = strlen(s + 1);
    for (int i = 1; i <= n; ++i) s[i] -= 48;
    for (int i = 1, tmp = 1; i <= n; ++i)
    {
        f[i] = add(f[i - 1], i);
        g[i] = add(g[i - 1], mul(i, tmp));
        k[n - i + 1] = mul(s[n - i + 1], tmp);
        tmp = mul(tmp, 10);
    }
    int res = 0;
    for (int i = 1; i <= n; ++i)
    {
        int left = i - 1, right = n - i;
        if (left) res = add(res, mul(f[left], k[i]));
        if (right) res = add(res, mul(g[right], s[i]));
    }
    printf("%d\n",res);
    return 0;
}