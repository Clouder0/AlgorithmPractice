#include <cstdio>
#include <cstring>
const int base = 137;
const int maxn = 1e5 + 100;
const int mods[2] = {1000000007, 998244353};
inline int mul(const int& a, const int& b, const int& mod)
{
    long long ret = 1ll * a * b;
    return ret >= mod ? ret % mod : ret;
}
inline int add(const int& a, const int& b, const int& mod)
{
    int ret = a + b;
    return ret >= mod ? ret - mod : ret;
}
inline int sub(const int& a, const int& b, const int& mod)
{
    int ret = a - b;
    return ret < 0 ? ret + mod : ret;
}
int n, m, bpow[2][maxn], f[2][maxn];
char s[maxn];
inline int substr(const int& l, const int& r, const int& t)
{
    return sub(f[t][r], mul(f[t][l - 1], bpow[t][r - l + 1], mods[t]), mods[t]);
}
int main()
{
    scanf("%s", s + 1), n = strlen(s + 1);
    bpow[0][0] = bpow[1][0] = 1;
    for (int i = 1; i <= n; ++i) bpow[0][i] = mul(bpow[0][i - 1], base, mods[0]), bpow[1][i] = mul(bpow[1][i - 1], base, mods[1]);
    for (int t = 0; t < 2; ++t)
        for (int i = 1; i <= n; ++i)
            f[t][i] = add(mul(f[t][i - 1], base, mods[t]), s[i], mods[t]);
    scanf("%d", &m);
    while (m--)
    {
        int l1, r1, l2, r2;
        scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
        puts((substr(l1, r1, 0) == substr(l2, r2, 0) && substr(l1, r1, 1) == substr(l2, r2, 1)) ? "YES" : "NO");
    }
    return 0;
}