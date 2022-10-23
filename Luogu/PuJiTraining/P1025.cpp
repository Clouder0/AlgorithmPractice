#include <cstdio>
using namespace std;
int n, k;
int dp[210][10];
int main()
{
    scanf("%d%d", &n, &k);
    dp[0][0] = 1;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= k; ++j)
            if (i >= j)
                dp[i][j] = dp[i - j][j] + dp[i - 1][j - 1];
    printf("%d", dp[n][k]);
    return 0;
}