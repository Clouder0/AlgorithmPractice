#include <algorithm>
#include <cstdio>
const int maxn = 5100;
int n, m, a[maxn], b[maxn], f[maxn][maxn];
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    for (int i = 1; i <= m; ++i) scanf("%d", b + i);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            if (a[i] == b[j])
                f[i][j] = f[i - 1][j - 1] + 1;
            else
                f[i][j] = std::max(f[i - 1][j], f[i][j - 1]);
        }
    printf("%d\n", f[n][m]);
    return 0;
}