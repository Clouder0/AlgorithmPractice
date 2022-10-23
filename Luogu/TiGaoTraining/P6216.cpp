#include <algorithm>
#include <cstdio>
const int maxn = 6e6 + 100;
unsigned int n, m, d[maxn], pi[maxn], sum[maxn], msum[maxn], res;
char s1[maxn], s2[maxn];
inline unsigned int getsum(int l, int r) { return sum[r] - sum[l - 1]; }
inline unsigned int getmsum(int l, int r) { return msum[r] - msum[l - 1]; }
int main()
{
    scanf("%u%u", &n, &m);
    scanf("%s%s", s1 + 1, s2 + 1);
    unsigned int l = 1, r = 0;
    for (unsigned int i = 1; i <= n; ++i)
    {
        if (i > r) for (d[i] = 1; i + d[i] <= n && i - d[i] > 0 && s1[i + d[i]] == s1[i - d[i]];) ++d[i];
        else
        {
            d[i] = std::min(r - i + 1, d[l + r - i]);
            for (; i + d[i] <= n && i - d[i] > 0 && s1[i + d[i]] == s1[i - d[i]];) ++d[i];
        }
        if (i + d[i] - 1 > r) l = i - d[i] + 1, r = i + d[i] - 1;
    }
    for (unsigned int i = 2, k = 0; i <= m; ++i)
    {
        while (k && s2[k + 1] != s2[i]) k = pi[k];
        if (s2[k + 1] == s2[i]) ++k;
        pi[i] = k;
    }
    for (unsigned int i = 1, k = 0; i <= n; ++i)
    {
        while (k && s2[k + 1] != s1[i]) k = pi[k];
        if (s2[k + 1] == s1[i]) ++k;
        if (k == m) sum[i - k + 1]++;
    }
    for (unsigned int i = 1; i <= n; ++i) msum[i] = msum[i - 1] + sum[i] * i, sum[i] += sum[i - 1];
    for (unsigned int i = 1; i <= n; ++i)
    {
        if (i + d[i] <= m) continue;
        unsigned int l = i - d[i] + 1, r = i + d[i] - m, mid = (2 * i - m + 1) / 2;
        res += getmsum(l, mid) - (i - d[i]) * getsum(l, mid);
        if (mid < r) res += getsum(mid + 1, r) * (i + d[i] + 1 - m) - getmsum(mid + 1, r);
    }
    printf("%u", res);
    return 0;
}