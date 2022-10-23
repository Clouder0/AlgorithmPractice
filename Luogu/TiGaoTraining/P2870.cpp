#include <cstdio>
#include <cstring>
#include <algorithm>
const int maxn = 1e6 + 100;
char s[maxn];
int n, m, sa[maxn], rk[maxn], oldrk[maxn], tp[maxn], tax[maxn];
void RadixSort()
{
    for (int i = 1; i <= m; ++i) tax[i] = 0;
    for (int i = 1; i <= n; ++i) tax[rk[i]]++;
    for (int i = 1; i <= m; ++i) tax[i] += tax[i - 1];
    for (int i = n; i; --i) sa[tax[rk[tp[i]]]--] = tp[i];
}
inline bool cmp(int a, int b, int w) { return oldrk[a] == oldrk[b] && oldrk[a + w] == oldrk[b + w]; }
void SuffixSort()
{
    m = 300;
    for (int i = 1; i <= n; ++i) rk[i] = s[i], tp[i] = i;
    RadixSort();
    for (int w = 1, p; p < n; w <<= 1, m = p)
    {
        p = 0;
        for (int i = n - w + 1; i <= n; ++i) tp[++p] = i;
        for (int i = 1; i <= n; ++i) if (sa[i] > w) tp[++p] = sa[i] - w;
        RadixSort();
        for (int i = 1; i <= n; ++i) oldrk[i] = rk[i];
        p = 0;
        for (int i = 1; i <= n; ++i) if(cmp(sa[i-1],sa[i],w)) rk[sa[i]] = p; else rk[sa[i]] = ++p;
    }
}
int main()
{
    scanf("%d",&n);
    for (int i = 1; i <= n; ++i)
    {
        static char t[10];
        scanf("%s", t + 1), s[i] = t[1];
    }
    int nn = 2 * n + 1;
    for (int i = 1; i <= n; ++i) s[nn - i + 1] = s[i];
    s[n + 1] = '#';
    std::swap(n, nn);
    SuffixSort();
    int num = 0, l = 1, r = nn;
    while (l <= r)
    {
        if (rk[l] < rk[n - r + 1]) putchar(s[l++]); else putchar(s[r--]);
        if ((++num) % 80 == 0) puts("");
    }
    return 0;
}