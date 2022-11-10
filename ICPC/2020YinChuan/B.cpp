#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1e4 + 100;
int n, a[maxn];
int f[2][maxn][4];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    int now = 0, last = 1;
    memset(f, -0x3f, sizeof(f));
    f[last][0][3] = 0;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= i; ++j)
        {
            f[now][j][0] = max(f[last][j][0], f[last][j - 1][3]);
            f[now][j][1] = max(f[last][j - 1][3] + a[i], max(f[last][j][0] + a[i], f[last][j][1]));
            f[now][j][2] = max(f[last][j - 1][3] - a[i], max(f[last][j][0] - a[i], f[last][j][2]));
            f[now][j][3] = max(f[last][j][1] - a[i], max(f[last][j][2] + a[i], max(f[last][j][3], f[last][j - 1][3])));
        }
        last ^= 1, now ^= 1;
    }
    for (int i = 1; i <= n; ++i) printf("%d\n", f[last][i][3]);
    return 0;
}