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
const int maxn = 1e6 + 100;
int k, q;
long long f[7], ww[7][10], w[maxn];
long long dp[maxn];
int bit[maxn];
int pw[7] = {0, 1, 10, 100, 1000, 10000, 100000};
inline void work(int weight, long long value) { for (int i = 999999; i >= weight; --i) dp[i] = std::max(dp[i], dp[i - weight] + value); }
int main()
{
    read(k);
    for (int i = 1; i <= 6; ++i) read(f[i]), ww[i][3] = f[i], ww[i][6] = 2 * f[i], ww[i][9] = 3 * f[i];
    pw[0] = 1;
    for (int i = 1; i <= 999999; ++i)
    {
        bit[i] = bit[i / 10] + 1;
        dp[i] = dp[i % pw[bit[i]]] + ww[bit[i]][(i / pw[bit[i]])];
    }
    for (int i = 1; i <= 6; ++i)
    {
        int num = std::min(3 * (k - 1), 333333 / pw[i]);
        for (int j = 1; j <= num; num -= j, j <<= 1) work(3 * pw[i] * j, f[i] * j);
        if (num) work(3 * pw[i] * num, f[i] * num);
    }
    read(q);
    for (int i = 1,x; i <= q; ++i) read(x),printf("%lld\n",dp[x]);
    return 0;
}