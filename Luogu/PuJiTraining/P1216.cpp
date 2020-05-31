#include <cstdio>
using namespace std;
void read(int &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
int r;
int dp[1010];
int sa[1010];
inline int max(const int &a,const int &b){return a>b?a:b;}
int main()
{
    read(r);
    for(int i = 1;i<=r;++i)
    {
        for(int j = 1;j<=i;++j)
            read(sa[j]);
        for(int j = i;j;--j)
            dp[j] = max(dp[j-1],dp[j]) + sa[j];
    }
    int ans = 0;
    for(int i = 1;i<=r;++i)
        ans = max(ans,dp[i]);
    printf("%d",ans);
    return 0;
}