#include <cstdio>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c; r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
inline int max(const int &a,const int &b){return a>b?a:b;}
inline int min(const int &a,const int &b){return a<b?a:b;}
int n;
int w[1000];
int num = 1;
int dp[1000][610];
void init(int now)
{
    int x,y;
    read(x);
    read(w[now]);
    x <<= 1;
    if(w[now])
    {
        for(int i = x;i<=n;++i)
            dp[now][i] = min(w[now],(i-x)/5);
    }
    else
    {
        init(now<<1);
        init(now<<1|1);
        for(int i = x;i<=n;++i)
            for(int j = i-x;j>=0;--j)
                dp[now][i] = max(dp[now][i],dp[now<<1][j] + dp[now<<1|1][i-x-j]);
    }
}
int main()
{
    read(n);
    init(1);
    printf("%d",dp[1][n-1]);
    return 0;
}