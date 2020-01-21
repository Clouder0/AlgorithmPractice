#include <cstdio>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
int n,m;
long long dp[11][5000][110];
int st[5000],num[5000];
int tot;
inline void init(int x)
{
    for(int i = st[x];i;i>>=1)
        num[x] += i & 1;
    dp[1][x][num[x]] = 1;
}
int main()
{
    read(n);
    read(m);
    int maxs = 1<<n;
    for(int i = 0;i<maxs;++i)
        if((i & (i<<1)) == 0)
            st[++tot] = i,init(tot);
    for(int i = 2;i<=n;++i)
        for(int j = 1;j<=tot;++j)
            for(int k = 1;k<=tot;++k)
                if(!(st[j] & st[k]) && !((st[j] << 1) & st[k]) && !((st[j] >> 1) & st[k]))
                    for(int t = num[j];t<=m;++t)
                        dp[i][j][t] += dp[i-1][k][t - num[j]];
    long long ans = 0;
    for(int i = 1;i<=tot;++i)
        ans += dp[n][i][m];
    printf("%lld",ans);
    return 0;
}