#include <cstdio>
#include <algorithm>
#include <cmath>
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
    r = 0;
    for (c = nc(); !isdigit(c); c = nc());
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r;
}
const int maxn = 2e5 + 100, maxb = 1100;
const int mod = 1e9 + 7;
inline int add(int x, int y) { int res = x + y; return res >= mod ? res - mod : res; }
inline int mul(int x, int y) { return 1ll * x * y % mod; }
int n, m, a[maxn], bel[maxn], len;
int sum[maxb], pre[maxb][maxb], suf[maxb][maxb], L[maxb], R[maxb];
int ask(int l, int r)
{
    int lp = bel[l], rp = bel[r], res = 0;
    if (rp - lp <= 1)
    {
        for (int i = l; i <= r; ++i) res = add(res, a[i]);
        return res;
    }
    for (int i = lp + 1; i < rp; ++i) res = add(sum[i], res);
    for (int i = l; i <= R[lp]; ++i) res = add(res, a[i]);
    for (int i = L[rp]; i <= r; ++i) res = add(res, a[i]);
    return res;
}
int main()
{
    read(n),read(m);
    for (int i = 1; i <= n; ++i) read(a[i]);
    len = std::sqrt(n / 2);
    for (int i = 1; i <= n; ++i) bel[i] = (i - 1) / len + 1, R[bel[i]] = i, sum[bel[i]] = add(sum[bel[i]], a[i]);
    for (int i = 1; i <= bel[n]; ++i) L[i] = (i - 1) * len + 1;
    while (m--)
    {
        static int opt, l, r, x, y, z;
        read(opt);
        if(opt == 1) 
        {
            read(x), read(y), read(z);
            if (x >= len) for (int i = y; i <= n; i += x) a[i] = add(a[i], z), sum[bel[i]] = add(sum[bel[i]], z);
            else
            {
                for (int i = y; i <= x; ++i) pre[x][i] = add(pre[x][i], z);
                for (int i = 1; i <= y; ++i) suf[x][i] = add(suf[x][i], z);
            }
        }
        else
        {
            read(l), read(r);
            int res = ask(l, r);
            for (int i = 1; i < len; ++i)
            {
                int lp = (l - 1) / i + 1, rp = (r - 1) / i + 1;
                if (lp == rp) res = add(res, add(pre[i][(r - 1) % i + 1], mod - pre[i][(l - 1) % i]));
                else
                {
                    res = add(res, mul(add(rp, mod - lp - 1), pre[i][i]));
                    res = add(res, add(pre[i][(r - 1) % i + 1], suf[i][(l - 1) % i + 1]));
                }
            }
            printf("%d\n", res);
        }
    }
    return 0;
}