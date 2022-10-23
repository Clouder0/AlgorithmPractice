#include <cstdio>
#include <cstring>
const int maxn = 16, maxlen = 52;
const int mod = 1000003;
int T, n, k;
char s[maxn][maxlen];
int match[maxlen][28];
int f[maxlen][1 << maxn];
int popcount[1 << maxn];
int main()
{
    scanf("%d", &T);
    for (int i = 1; i < (1 << 15); ++i) popcount[i] = popcount[i >> 1] + (i & 1);
    while (T--)
    {
        scanf("%d%d", &n, &k);
        for (int i = 1; i <= n; ++i) scanf("%s", &s[i][1]);
        int len = strlen(&s[1][1]);
        for (int c = 0; c < 26; ++c) for (int i = 1; i <= len; ++i) match[i][c] = (1 << n) - 1;
        for (int i = 1; i <= len; ++i) for (int j = 0; j < (1 << n); ++j) f[i][j] = 0;
        for (int c = 0; c < 26; ++c)
            for (int i = 1; i <= n; ++i)
                for (int j = 1; j <= len; ++j)
                    if (s[i][j] != 'a' + c && s[i][j] != '?')
                        match[j][c] &= (~(1 << (i - 1)));
        f[0][(1 << n) - 1] = 1;
        for (int i = 1; i <= len; ++i)
            for (int c = 0; c < 26; ++c)
                for (int k = 0; k < (1 << n); ++k)
                    f[i][k & match[i][c]] = (f[i][k & match[i][c]] + f[i - 1][k]) % mod;
        int res = 0;
        for (int i = 0; i < (1 << n); ++i)
            if (popcount[i] == k) res = (res + f[len][i]) % mod;
        printf("%d\n", res);
    }
    return 0;
}