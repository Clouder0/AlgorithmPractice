#include <cstdio>
#include <cstring>
const int maxn = 1e6 + 100;
char s[maxn];
int n, m, sa[maxn], rk[maxn], tp[maxn], tax[maxn], oldrk[maxn];
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
    for (int i = 1; i <= n; ++i) rk[i] = s[i],tp[i] = i;
    RadixSort();
    for (int w = 1, p; p < n; w <<= 1, m = p)
    {
        p = 0;
        for (int i = n - w + 1; i <= n; ++i) tp[++p] = i;
        for (int i = 1; i <= n; ++i) if (sa[i] > w) tp[++p] = sa[i] - w;
        RadixSort();
        for (int i = 1; i <= n; ++i) oldrk[i] = rk[i];
        p = 0;
        for (int i = 1; i <= n; ++i) if (cmp(sa[i - 1], sa[i], w)) rk[sa[i]] = p; else rk[sa[i]] = ++p;
    }
}
int main()
{
    scanf("%s", s + 1);
    n = strlen(s + 1);
    for (int i = 1; i <= n; ++i) s[i + n] = s[i];
    n <<= 1;
    SuffixSort();
    int on = n >> 1;
    for (int i = 1; i <= n; ++i) if(sa[i] <= on) putchar(s[sa[i] + on - 1]);
    return 0;
}