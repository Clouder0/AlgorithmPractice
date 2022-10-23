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
int dp[1000][610];
int w[40];
int v[40];
void init(int now)
{
    int t,x;
    read(t);
    read(x);
    t <<= 1;
    if(x)
    {
        for(int i = 1;i<=x;++i)
            read(v[i]),read(w[i]);
        for(int j = 1;j<=x;++j)
            for(int i = n;i>=w[j]+t;--i)
                dp[now][i] = max(dp[now][i],dp[now][i-w[j]] + v[j]);
    }
    else
    {
        init(now<<1);
        init(now<<1|1);
        for(int i = t;i<=n;++i)
            for(int j = i-t;j>=0;--j)
                dp[now][i] = max(dp[now][i],dp[now<<1][j] + dp[now<<1|1][i-t-j]);
    }
}
int main()
{
    read(n);
    init(1);
    printf("%d",dp[1][n-1]);
    return 0;
}