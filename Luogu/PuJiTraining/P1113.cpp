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
int n,ans;
int dp[20000];
int main()
{
    read(n);
    int temp,temp2,num;
    for(int i = 1;i<=n;++i)
    {
        read(num);
        read(dp[num]);
        temp2 = 0;
        read(temp);
        while(temp != 0)
        {
            temp2 = max(temp2,dp[temp]);
            read(temp);
        }
        dp[num] += temp2;
        ans = max(ans,dp[num]);
    }
    printf("%d",ans);
    return 0;
}