#include <cstdio>
#include <cstring>
using namespace std;
void read(int &r)
{
    static char c;r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar());
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar());
}
inline int min(const int &a, const int &b) { return a < b ? a : b; }
inline int max(const int &a, const int &b) { return a > b ? a : b; }
int n,ans;
int sum[210];
int dp[210][210];
int main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        read(sum[i]);
        sum[i + n] = sum[i];
    }
    for (int i = 1; i <= n << 1; ++i)
        sum[i] += sum[i - 1];
    memset(dp,0x3f,sizeof(dp));
    for(int i = 1;i<=n<<1;++i)
        dp[i][i] = 0;
    for (int len = 1; len < n; ++len)
        for (int l = 1, r = 1 + len; l + len <= n << 1; ++l, r = l + len)
            for (int k = l; k < r; ++k)
                dp[l][r] = min(dp[l][r], dp[l][k] + dp[k + 1][r] + sum[r] - sum[l - 1]);
    ans = 999999999;
    for(int i = 1;i<=n;++i)
        ans = min(ans,dp[i][i+n-1]);
    printf("%d\n",ans);
    memset(dp,0,sizeof(dp));
    for (int len = 1; len < n; ++len)
        for (int l = 1, r = 1 + len; l + len <= n << 1; ++l, r = l + len)
            for (int k = l; k < r; ++k)
                dp[l][r] = max(dp[l][r], dp[l][k] + dp[k + 1][r] + sum[r] - sum[l - 1]);
    ans = 0;
    for(int i = 1;i<=n;++i)
        ans = max(ans,dp[i][i+n-1]);
    printf("%d\n",ans);
    return 0;
}