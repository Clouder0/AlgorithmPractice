#include <cstdio>
#include <cstring>
#include <algorithm>
const int maxn = 1e5 + 100;
char s[maxn], t[maxn];
int n, pi[18][maxn], z[maxn], res[maxn];
void kmp()
{
    for (int i = 2, k = 0; i <= n; ++i)
    {
        while(k && t[i] != t[k + 1]) k = pi[0][k];
        if (t[i] == t[k + 1]) ++k;
        pi[0][i] = k;
    }
}
void z_algorithm()
{
    int l = 0, r = -1;
    for (int i = 2; i <= n; ++i)
    {
        if (i > r) for (z[i] = 0; i + z[i] <= n && s[i + z[i]] == s[z[i] + 1];) ++z[i];
        else
        {   //[l,r] -> i \in [l,r] matches with [1,r - l + 1]
            if (z[i - l + 1] < r - i + 1) z[i] = z[i - l + 1];
            else for (z[i] = r - i + 1; i + z[i] <= n && s[i + z[i]] == s[z[i] + 1];) ++z[i];
        }
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
}
int main()
{
    scanf("%s",s + 1);
    n = strlen(s + 1);
    for (int i = 1; i <= n; ++i) t[i] = s[n - i + 1];
    kmp(), z_algorithm();
    z[1] = n;
    int maxx = 0;
    while ((1 << maxx) < n) ++maxx;
    for (int t = 1; t <= maxx; ++t)
        for (int i = 1; i <= n; ++i) pi[t][i] = pi[t - 1][pi[t - 1][i]];
    for (int i = 1; i <= n; ++i)
    {
        //enumrate L
        int pre = z[i], suf = pi[0][n - i + 1];
        if (pre >= n - i + 1) { res[n - i + 1]++; continue; }
        if (pre >= suf) { res[suf]++; continue; }
        for (int t = maxx; t >= 0; --t)
            if (pi[t][suf] > pre) suf = pi[t][suf];
        suf = pi[0][suf];
        res[suf]++;
    }
    for (int i = n; i; --i) if (res[i] > 0) res[pi[0][i]] += res[i];
    int num = 0;
    for (int i = 1; i <= n; ++i) num += res[i] > 0;
    printf("%d\n", num);
    for (int i = 1; i <= n; ++i) if (res[i] > 0) printf("%d %d\n", i, res[i]);
    return 0;
}