#include <cstdio>
#include <cstring>
using namespace std;
int n, k;
int dp[610][610];
int *f[200100];
inline int min(const int &a,const int &b){return a<b?a:b;}
int main()
{
    scanf("%d%d", &n, &k);
    int p = 0;
    for (int i = 0; i <= n; ++i)
    {
        if (p >= 600)
            p -= 600;
        f[i] = dp[p + 1];
        ++p;
    }
    f[0][0] = 1;
    int i, j;
    for (i = 1; i <= n; ++i)
    {
        memset(f[i], 0, sizeof(f[i]));
        for (j = min(k,i); j; --j)
            f[i][j] = (f[i - j][j] + f[i - 1][j - 1]) % 10086;
    }
    printf("%d", f[n][k]);
    return 0;
}
