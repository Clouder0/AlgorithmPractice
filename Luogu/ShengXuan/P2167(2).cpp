#include <cstdio>
#include <cstring>
const int mod = 1000003;
const int maxn = 16, maxlen = 52;
int T, n, k, len;
char s[maxn][maxlen];
int C[20][20], popcount[1 << maxn];
char vis[maxlen];
inline int calc(int x)
{
    for (int i = 1; i <= len; ++i) vis[i] = 0;
    for (int i = 1; i <= len; ++i)
        for (int j = 1; j <= n; ++j)
            if (((1 << (j - 1)) & x) && s[j][i] != '?')
            {
                if (vis[i] && vis[i] != s[j][i]) return 0;
                vis[i] = s[j][i];
            }
    int res = 1;
    for (int i = 1; i <= len; ++i) if (!vis[i]) res = (res * 26) % mod;
    return res;
}
int main()
{
    scanf("%d", &T);
    for (int i = 1; i < (1 << 15); ++i) popcount[i] = popcount[i >> 1] + (i & 1);
    C[0][0] = 1;  //C(n,m) = C(n-1,m) + C(n-1,m)
    for (int i = 1; i < 20; ++i)
    {
        C[i][0] = 1;
        for (int j = 1; j <= i; ++j) C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
    }
    while (T--)
    {
        scanf("%d %d", &n, &k);
        for (int i = 1; i <= n; ++i) scanf("%s", s[i] + 1);
        len = strlen(s[1] + 1);
        int res = 0;
        for (int i = 0; i < (1 << n); ++i)
        {
            if (popcount[i] < k) continue;
            int flag = ((popcount[i] - k) & 1) ? -1 : 1;
            res = (((res + 1ll * flag * C[popcount[i]][k] * calc(i)) % mod) + mod) % mod;
        }
        printf("%d\n", res);
    }
    return 0;
}