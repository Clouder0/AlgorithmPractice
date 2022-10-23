#include <cstdio>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c; r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
int n,m,t;
int dp[210][210];
int w1[110],w2[110];
int main()
{
    read(n);
    read(m);
    read(t);
    for(int i = 1;i<=n;++i)
    {
        read(w1[i]);
        read(w2[i]);
    }
    for(int i = 1;i<=n;++i)
        for(int j = m;j>=w1[i];--j)
            for(int k = t;k>=w2[i];--k)
                if(dp[j][k] < dp[j-w1[i]][k-w2[i]] + 1)
                    dp[j][k] = dp[j-w1[i]][k-w2[i]] + 1;
    int ans = 0;
    for(int i = 0;i<=m;++i)
        for(int j = 0;j<=t;++j)
            if(ans < dp[i][j])
                ans = dp[i][j];
    printf("%d",ans);
    return 0;
}