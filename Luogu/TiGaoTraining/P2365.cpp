#include <cstdio>
#include <cstring>
using namespace std;
template<typename T>
inline T min(const T &a,const T &b){return a<b?a:b;}
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 5e3 + 10;
int n,s;
int t[maxn];
int f[maxn];
int ts[maxn],fs[maxn];
int dp[maxn];
int main()
{
    read(n);
    read(s);
    for(int i = 1;i<=n;++i)
        read(t[i]),read(f[i]),ts[i] = ts[i-1] + t[i],fs[i] = fs[i-1] + f[i];
    memset(dp,0x3f,sizeof(dp));
    dp[0] = 0;
    for(int i = 1;i<=n;++i)
        for(int j = 1;j<=i;++j)
            dp[i] = min(dp[i],dp[j-1] + ts[i] * (fs[i] - fs[j-1]) + s * (fs[n] - fs[j-1]));
    printf("%d",dp[n]);
    return 0;
}