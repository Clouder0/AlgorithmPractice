#include <cstdio>
using namespace std;
inline char nc()
{
    static char buf[100000],*p1 = buf,*p2 = buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
void read(int &r)
{
    static char c;static int flag;flag = 1,r=0;
    for(c=nc();c>'9'||c<'0';c=nc())  if(c == '-') flag = -1;
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=nc());
    r *= flag;
}
inline int max(const int &a,const int &b){return a>b?a:b;}
int n,temp,ans = -9999999,dp[2];
int main()
{
    read(n);
    for(int i = 1;i<=n;ans = max(dp[i&1] = max(dp[(i-1)&1] + temp,temp),ans),++i)
        read(temp);
    printf("%d",ans);
    return 0;
}