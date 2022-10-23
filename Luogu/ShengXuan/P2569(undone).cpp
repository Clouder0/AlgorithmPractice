#include <cstdio>
#include <memory.h>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
template<typename T>
inline T max(const T &a,const T &b){return a>b?a:b;}
const int maxn = 2e3 + 10;
int T,MaxP,W;
int AP[maxn],BP[maxn],AS[maxn],BS[maxn];
int dp[maxn][maxn];
int main()
{
    memset(dp,~0x3f,sizeof(dp));
    read(T);
    read(MaxP);
    read(W);
    for(int i = 1;i<=T;++i)
        read(AP[i]),read(BP[i]),read(AS[i]),read(BS[i]);
    dp[0][0] = 0;
    for(int i = 1;i<=T;++i)
    {
        for(int p = 0;p<=MaxP;++p)
            dp[i][p] = max(dp[i][p],dp[i-1][p]);
        dp[i][AS[i]] = max(dp[i][AS[i]],-(AP[i]*AS[i]));
        if(i-W-1 < 0)
            continue;
        for (int k = 0; k <= MaxP; ++k)
            for (int p = max(AS[i]-k,0); p <= k; ++p)
                dp[i][k] = max(dp[i][k],dp[i-W-1][p] - (k-p)*AP[i]);
        for(int k = 0; k <= MaxP;++k)
            for(int p = k;p<=k+BS[i]&&p<=MaxP;++p)
                dp[i][k] = max(dp[i][k],dp[i-W-1][p] + (p-k)*BP[i]);
    }
    int ans = -(1<<30);
    for(int i = 0;i<=MaxP;++i)
        if(dp[T][i] > ans)
            ans = dp[T][i];
    printf("%d",ans);
    return 0;
}