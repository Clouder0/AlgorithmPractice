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
int n;
int b[210],c[210];
int dp[21000];
int cnt,w[10000],v[10000];
int k;
template<typename T>
inline T min(const T &a,const T &b)
{return a<b?a:b;}
int main()
{
    read(n);
    for(int i = 1;i<=n;++i)
        read(b[i]);
    for(int i = 1;i<=n;++i)
        read(c[i]);
    read(k);
    for(int i = 1;i<=n;++i)
    {
        for(int p = 1;p<=c[i];p<<=1)
            w[++cnt] = b[i]*p,v[cnt] = p,c[i]-=p;
        if(c[i])
            w[++cnt] = b[i]*c[i],v[cnt] = c[i];
    }
    memset(dp,0x3f,sizeof(dp));
    dp[0] = 0;
    for(int i = 1;i<=cnt;++i)
        for(int p = k;p>=w[i];--p)
            dp[p] = min(dp[p],dp[p-w[i]] + v[i]);
    printf("%d",dp[k]);
    return 0;
}