#include <cstdio>
const int maxn = 110;
const long long mod = 1000000007;
int n, m, k, cnt;
char s1[maxn], s2[maxn];
long long c[maxn][maxn];
inline void init()
{
    c[1][1] = 1ll;
    for (int i = 2; i <= n + 5; ++i)
        for (int j = 1; j <= i; ++j)
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
}
struct matrix
{
    int n, m;
    long long a[maxn][maxn];
    matrix(int n, int m)
    {
        this->n = n, this->m = m;
        for (int i = 1; i <= n; ++i) 
            for (int j = 1; j <= m; ++j)
                a[i][j] = 0;
    }
    matrix operator*(const matrix b)
    {
        matrix res(n, b.m);
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                for (int k = 1; k <= b.m; ++k)
                    res.a[i][k] = (res.a[i][k] + a[i][j] * b.a[j][k]) % mod;
        return res;
    }
};
signed main()
{
    scanf("%d %d %d", &n, &k, &m), init();
    scanf("%s", s1 + 1), scanf("%s", s2 + 1);
    for (int i = 1; i <= n; ++i) cnt += (s1[i] == s2[i]);
    matrix A(n + 1, n + 1), S(1, n + 1), T(n + 1, n + 1);
    for (int i = 0; i <= n; ++i) for (int j = 0; j <= m; ++j)
    {
        int num = i + m - 2 * j;
        if (num > n || num < 0) continue;
        A.a[i + 1][num + 1] = (A.a[i + 1][num + 1] + c[i + 1][j + 1] * c[n - i + 1][m - j + 1]) % mod;
    }
    S.a[1][cnt + 1] = 1;
    for (int i = 1; i <= T.n; ++i) T.a[i][i] = 1;
    for (; k; k >>= 1)
    {
        if (k & 1) T = T * A;
        A = A * A;
    }
    S = S * T;
    printf("%lld\n", S.a[1][n + 1]);
    return 0;
}