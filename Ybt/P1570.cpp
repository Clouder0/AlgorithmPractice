#include <cstdio>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
int n;
int head[1000],tail[1000];
int dp[1000][1000];
inline int max(const int &a,const int &b){return a>b?a:b;}
int main()
{
    read(n);
    for(int i = 1;i<=n;++i)
        read(head[i]),head[i+n] = head[i];
    int n2 = n << 1;
    for(int i = 1;i<n2;++i)
        tail[i] = head[i+1];
    tail[n2] = head[1];
    for(int len = 1;len<=n;++len)
        for(int i = 1;i+len<=n2;++i)
            for(int k = i;k<i+len;++k)
                dp[i][i+len] = max(dp[i][i+len],dp[i][k] + dp[k+1][i+len] + head[i] * tail[k] * tail[i+len]);
    int ans = 0;
    for(int i = 1;i<=n;++i)
        ans = max(ans,dp[i][i+n-1]);
    printf("%d",ans);
    return 0;
}