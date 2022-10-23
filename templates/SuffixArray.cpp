#include <cstdio>
#include <algorithm>
#include <cstring>
const int maxn = 1e6 + 100;
char s[maxn];
int n, M, sa[maxn], rk[maxn << 1], oldrk[maxn << 1], tax[maxn], tp[maxn], height[maxn], h[maxn];
void RadixSort()
{
    for (int i = 1; i <= M; ++i) tax[i] = 0;
    for (int i = 1; i <= n; ++i) tax[rk[i]]++;          //统计第一关键字排名为 i 的有多少个
    for (int i = 1; i <= M; ++i) tax[i] += tax[i - 1];  //做前缀和方便得到全局排名
    for (int i = n; i; --i) sa[tax[rk[tp[i]]]--] = tp[i];  //倒序遍历，保证在第一关键字相同的中，第二关键字靠后的排名靠后
}
inline bool same(int a, int b, int w) { return oldrk[a] == oldrk[b] && oldrk[a + w] == oldrk[b + w]; }
void SuffixArray()
{
    M = 300;
    for (int i = 1; i <= n; ++i) rk[i] = s[i], tp[i] = i;
    RadixSort();
    for (int w = 1, p; p < n; w <<= 1, M = p)  //reset count range
    {
        p = 0;
        for (int i = n - w + 1; i <= n; ++i) tp[++p] = i;  //第二关键字为无穷小的先放入
        for (int i = 1; i <= n; ++i) if (sa[i] > w) tp[++p] = sa[i] - w;  //初始化第二关键字
        RadixSort();
        for (int i = 1; i <= n; ++i) oldrk[i] = rk[i];
        p = 0;
        for (int i = 1; i <= n; ++i) if (same(sa[i - 1], sa[i], w)) rk[sa[i]] = p; else rk[sa[i]] = ++p;
    }
}
void initHeight()
{
    for (int i = 1, k = 0; i <= n; ++i)
    {
        if (k) --k;
        while (s[i + k] == s[sa[rk[i] - 1] + k]) ++k;
        height[rk[i]] = h[i] = k;
    }
}
int main()
{
    scanf("%s", s + 1);
    n = strlen(s + 1);
    SuffixArray();
    for (int i = 1; i <= n; ++i) printf("%d ", sa[i]);
    return 0;
}