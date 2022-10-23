
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <ctype.h>
using namespace std;
const int bufSize = 1e6;
inline char nc()
{
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
const int maxn = 1e5 + 100;
const int maxm = 710;
int n, m, c, a[maxn];
int L[maxm], R[maxm], bel[maxn], len, blocknum, cnt[maxm][maxn], ans[maxm][maxm];
bool tmp[maxn], vis[maxn];
inline void init() 
{
    for (int i = 1; i <= n; ++i) bel[i] = (i - 1) / len + 1;
    for (int i = 1; i <= bel[n]; ++i) L[i] = R[i - 1] + 1, R[i] = L[i] + len - 1;
    R[blocknum = bel[n]] = n;
}
inline int get(int l, int r, int i) { return cnt[r][i] - cnt[l - 1][i]; }
inline int ask(int l, int r)
{
    int lpos = bel[l], rpos = bel[r], res = 0;
    if (rpos - lpos <= 2)
    {
        for (int i = l; i <= r; ++i) vis[a[i]] = tmp[a[i]] = 0;
        for (int i = l; i <= r; ++i) res -= !tmp[a[i]] - !vis[a[i]], res += !(tmp[a[i]] ^= 1), vis[a[i]] = 1;
        return res;
    }
    res = ans[lpos + 1][rpos - 1];
    for (int i = l; i <= R[lpos]; ++i) tmp[a[i]] = vis[a[i]] = 0;
    for (int i = L[rpos]; i <= r; ++i) tmp[a[i]] = vis[a[i]] = 0;
    for (int i = l, t; i <= R[lpos]; ++i) t = get(lpos + 1, rpos - 1, a[i]), tmp[a[i]] ^= (t & 1), vis[a[i]] |= (t > 0);
    for (int i = L[rpos], t; i <= r; ++i) t = get(lpos + 1, rpos - 1, a[i]), tmp[a[i]] ^= (t & 1), vis[a[i]] |= (t > 0);
    for (int i = l; i <= R[lpos]; ++i) res -= !tmp[a[i]] - !vis[a[i]], res += !(tmp[a[i]] ^= 1), vis[a[i]] = 1;
    for (int i = L[rpos]; i <= r; ++i) res -= !tmp[a[i]] - !vis[a[i]], res += !(tmp[a[i]] ^= 1), vis[a[i]] = 1;
    return res;
}
int main()
{
    read(n), read(c), read(m);
    for (int i = 1; i <= n; ++i) read(a[i]);
    len = sqrt(n / 2), init();
    for (int i = 1; i <= blocknum; ++i)
    {
        for (int j = 0; j <= c; ++j) cnt[i][j] = cnt[i - 1][j];
        for (int j = L[i]; j <= R[i]; ++j) cnt[i][a[j]]++;
    }
    for (int i = 1; i <= blocknum; ++i)
    {
        for (int j = 0; j <= c; ++j) vis[j] = tmp[j] = 0;
        for (int j = i; j <= blocknum; ++j, ans[i][j] = ans[i][j - 1])
        {
            for (int k = L[j]; k <= R[j]; ++k) ans[i][j] += !vis[a[k]], vis[a[k]] = 1;
            for (int k = L[j]; k <= R[j]; ++k) ans[i][j] -= !(tmp[a[k]]), ans[i][j] += !(tmp[a[k]] ^= 1);
        }
    }
    for (int i = 1, l, r, lans = 0; i <= m; ++i)
    {
        read(l), read(r);
        l = (l + lans) % n + 1, r = (r + lans) % n + 1;
        printf("%d\n", lans = l < r ? ask(l, r) : ask(r, l));
    }
    return 0;
}
