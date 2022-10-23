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
const int _MOD = 998244353;
const int maxn = 2e5 + 100;
int n, m;
int prod[maxn], prodinv[maxn];
int fastpow(int a, int b)
{
    int ret = 1;
    while (b)
    {
        if (b & 1) ret = (1ll * ret * a) % _MOD;
        a = (1ll * a * a) % _MOD;
        b >>= 1;
    }
    return ret;
}
int C(int a, int b)
{
    if(a < 0) return 0;
    if(b < 0) return 0;
    if(a == b) return 1;
    if(b > a) return 0;
    return (((1ll * prod[a] * prodinv[b]) % _MOD) * prodinv[a - b]) % _MOD;
}
signed main()
{
    read(n), read(m);
    if (n == 2)
    {
        puts("0");
        return 0;
    }
    prod[0] = 1;
    for (int i = 1; i <= m; ++i) prod[i] = (1ll * prod[i - 1] * i) % _MOD;
    prodinv[m] = fastpow(prod[m], _MOD - 2);
    for (int i = m - 1; i >= 0; --i) prodinv[i] = (1ll * prodinv[i + 1] * (i + 1)) % _MOD;
    int res = 0;
    int t = fastpow(2, n - 3);
    printf("%lld\n", ((n - 2) * C(m, n - 1) % _MOD) * t % _MOD);
    return 0;
}