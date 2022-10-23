#include <cstdio>
#include <cstring>
using namespace std;
template<typename T>
inline T read(T &r)
{
    static char c;static int flag;flag = 1,r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar()) if(c == '-') flag = -1;
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
    return r*=flag;
}
int k,m,n;
int dp[110][20][6];
int all[3][110];
inline int max(const int &a,const int &b){return a>b?a:b;}
inline int max(const int &a,const int &b,const int &c){return max(c,max(a,b));}
inline int max(const int &a,const int &b,const int &c,const int &d){return max(d,max(a,b,c));}
inline int max(const int &a,const int &b,const int &c,const int &d,const int &e){return max(e,max(a,b,c,d));}
int main()
{
    read(n);
    read(m);
    read(k);
    memset(dp,-0x3f3f3f3f,sizeof(dp));
    for(int i=0;i<=n;i++)
        for(int j=0;j<=k;j++)
            dp[i][j][0]=0;
    for(int i = 1;i<=n;++i)
        for(int j = 1;j<=m;++j)
            read(all[j][i]);
    if(m == 1)
    {
        for(int i = 1;i<=n;++i)
            for(int j = 1;j<=k;++j)
            {
                dp[i][j][0] = max(dp[i-1][j][0],dp[i-1][j][1]);
                dp[i][j][1] = max(dp[i-1][j][1],dp[i-1][j-1][0]) + all[1][i];
            }
        printf("%d",max(dp[n][k][0],dp[n][k][1]));
        return 0;
    }
    for(int i = 1;i<=n;++i)
    {
        for(int j = 1;j<=k;++j)
        {
            dp[i][j][0] = max(dp[i-1][j][0],dp[i-1][j][1],dp[i-1][j][2],dp[i-1][j][3],dp[i-1][j][4]);
            dp[i][j][1] = max(dp[i-1][j-1][0],dp[i-1][j][1],dp[i-1][j-1][2],dp[i-1][j][3],dp[i-1][j-1][4]) + all[1][i];
            dp[i][j][2] = max(dp[i-1][j-1][0],dp[i-1][j-1][1],dp[i-1][j][2],dp[i-1][j][3],dp[i-1][j-1][4]) + all[2][i];
            dp[i][j][3] = max(dp[i-1][j-1][1],dp[i-1][j-1][2],dp[i-1][j][3]) + all[1][i] + all[2][i];
            if(j > 1) dp[i][j][3] = max(dp[i][j][3],dp[i-1][j-2][0] + all[1][i] + all[2][i],dp[i-1][j-2][4] + all[1][i] + all[2][i]);
            dp[i][j][4] = max(dp[i-1][j-1][0],dp[i-1][j-1][1],dp[i-1][j-1][2],dp[i-1][j-1][3],dp[i-1][j][4]) + all[1][i] + all[2][i];
        }
    }
    printf("%d",max(dp[n][k][0],dp[n][k][1],dp[n][k][2],dp[n][k][3],dp[n][k][4]));
    return 0;
}