#include <cstdio>
#include <cstring>
const int maxn = 1e6 + 100;
const unsigned int mods[2] = {1000000007, 998244353};
const unsigned int b = 31;
char s[maxn];
unsigned int bpow[2][maxn], f[2][maxn];
int n, m;
inline int getSub(int l, int r, int t) { return (f[t][r] + mods[t] - 1ll * f[t][l - 1] * bpow[t][r - l + 1] % mods[t]) % mods[t]; }
inline bool isEqual(int l1, int r1, int l2, int r2)
{
    return getSub(l1, r1, 0) == getSub(l2, r2, 0) && getSub(l1, r1, 1) == getSub(l2, r2, 1);
}
int main()
{
    scanf("%s", s + 1);
    n = strlen(s + 1);
    for (int t = 0; t < 2; ++t)
    {
        bpow[t][0] = 1;
        for (int i = 1; i <= n; ++i) bpow[t][i] = 1ll * bpow[t][i - 1] * b % mods[t];
    }
    for (int t = 0; t < 2; ++t)
        for (int i = 1; i <= n; ++i) f[t][i] = (1ll * f[t][i - 1] * b % mods[t] + s[i] * b) % mods[t];
    scanf("%d", &m);
    for (int i = 1, l1, r1, l2, r2; i <= m; ++i)
    {
        scanf("%d %d %d %d", &l1, &r1, &l2, &r2);
        puts(isEqual(l1, r1, l2, r2) ? "YES" : "NO");
    }
    return 0;
}