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
const int maxn = 5100;
int k, q, d[maxn], nd[maxn];
long long sum[maxn];
int main()
{
    read(k),read(q);
    for (int i = 1; i <= k; ++i) read(d[i]);
    for (int i = 1, n, x, m; i <= q; ++i)
    {
        read(n), read(x), read(m);
        --n;
        int res = n, zeronum = 0;
        for (int j = 1; j <= k; ++j) nd[j] = d[j] % m, sum[j] = sum[j - 1] + nd[j], zeronum += !nd[j];
        res -= n / k * zeronum;
        for (int j = 1; j <= n % k; ++j) res -= !nd[j];
        long long tsum = x + n / k * sum[k] + sum[n % k];
        res -= tsum / m - x / m;
        printf("%d\n",res);
    }
    return 0;
}