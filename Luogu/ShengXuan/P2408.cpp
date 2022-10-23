#include <cstdio>
const int maxn = 2e5 + 100;
int n, m, rk[maxn], sa[maxn], tp[maxn], oldrk[maxn], tax[maxn], h[maxn];
char s[maxn];
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
    m = 300;
    for (int i = 1; i <= n; ++i) rk[i] = s[i],tp[i] = i;
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
    for (int i = 1, k = 0, j; i <= n; ++i)
    {
        if(k) --k;
        j = sa[rk[i] - 1];
        while (s[i + k] == s[j + k]) ++k;
        h[i] = k;
    }
}
int main()
{
    scanf("%d",&n);
    scanf("%s",s + 1);
    SuffixSort();
    long long res = (1ll * n * (n + 1)) >> 1;
    for (int i = 1; i <= n; ++i) res -= h[i];
    printf("%lld\n", res);
    return 0;
}