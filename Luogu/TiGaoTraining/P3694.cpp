#include <cstdio>
#include <cstring>
using namespace std;
template<typename T>
inline T min(const T &a,const T &b){return a<b?a:b;}
template<typename T>
void read(T &r){static char c;r=0;for(c=getchar();c>'9'||c<'0';c=getchar());for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());}
const int maxn = 1e5 + 10;
const int maxm = 21;
int n,m;
int a[maxn];
int num[maxm];
int s[maxn][maxm];
int len[1<<maxm];
int dp[1<<maxm];
int dfs(int status)
{
    if(dp[status] != 1<<30)
        return dp[status];
    for (int i = 1; i <= m; ++i)
        if(status & (1<<(i-1)))
        {
            int l = len[status] - num[i] + 1,r = len[status];
            dp[status] = min(dp[status],dfs(status ^ (1<<(i-1))) + num[i] - (s[r][i] - s[l-1][i]));
        }
    return dp[status];
}
int main()
{
    read(n);
    read(m);
    for(int i = 1;i<=n;++i)
        read(a[i]),num[a[i]]++,s[i][a[i]]++;
    for(int i = 1;i<=n;++i)
        for(int j = 1;j<=m;++j)
            s[i][j] += s[i-1][j];
    int maxs = (1<<m) - 1;
    for(int i = 1;i<=maxs;++i)
        dp[i] = 1<<30;
    for(int i = 1;i<=maxs;++i)
        for(int j = 1;j<=m;++j)
            if(i & (1<<(j-1)))
                len[i] += num[j];
    printf("%d",dfs((1<<m)-1));
    return 0;
}