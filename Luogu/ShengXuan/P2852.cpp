#include <cstdio>
#include <algorithm>
const int maxn = 2e6 + 100;
int n, m, k, a[maxn], rk[maxn], tp[maxn], sa[maxn], oldrk[maxn], tax[maxn], ht[maxn];
void RadixSort()
{
    for (int i = 1; i <= m; ++i) tax[i] = 0;
    for (int i = 1; i <= n; ++i) tax[rk[i]]++;
    for (int i = 1; i <= m; ++i) tax[i] += tax[i - 1];
    for (int i = n; i; --i) sa[tax[rk[tp[i]]]--] = tp[i];
}
inline bool cmp(const int& a, const int& b, const int& w) { return oldrk[a] == oldrk[b] && oldrk[a + w] == oldrk[b + w]; }
void SuffixSort()
{
    m = 1000000;
    for (int i = 1; i <= n; ++i) rk[i] = a[i],tp[i] = i;
    RadixSort();
    for (int w = 1, p = 0; p < n; w <<= 1, m = p)
    {
        p = 0;
        for (int i = n - w + 1; i <= n; ++i) tp[++p] = i;
        for (int i = 1; i <= n; ++i) if (sa[i] > w) tp[++p] = sa[i] - w;
        RadixSort();
        for (int i = 1; i <= n; ++i) oldrk[i] = rk[i];
        p = 0;
        for (int i = 1; i <= n; ++i) if (cmp(sa[i - 1], sa[i], w)) rk[sa[i]] = p; else rk[sa[i]] = ++p;
    }
    for (int i = 1, k = 0; i <= n; ++i)
    {
        if (k) --k;
        while (a[i + k] == a[sa[rk[i] - 1] + k]) ++k;
        ht[rk[i]] = k;
    }
}
int main()
{
    scanf("%d %d",&n,&k);
    for (int i = 1; i <= n; ++i) scanf("%d",a + i);
    SuffixSort();
    static int qt = 0, qh = 1, q[maxn],res = 0;
    for (int i = 1; i <= n; ++i) 
    {
        while (qt >= qh && ht[i] <= ht[q[qt]]) --qt;
        q[++qt] = i;
        while (i - q[qh] >= k - 1) ++qh;
        if (qt >= qh) res = std::max(res, ht[q[qh]]);
    }
    printf("%d\n", res);
    return 0;
}