#include <cstdio>
#include <cstring> 
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 1e5 + 100;
int n;
int a[maxn],b[maxn],c[maxn];
int dp[maxn],len;
int main()
{
    read(n);
    for(int i = 1;i<=n;++i)
        read(a[i]);
    for(int i = 1;i<=n;++i)
        c[a[i]] = i;
    for(int i = 1;i<=n;++i)
        read(b[i]),b[i] = c[b[i]];
    memset(dp,0x3f,sizeof(dp));
    len = 1,dp[1] = b[1];
    for(int i = 2;i<=n;++i)
    {
        if(b[i] > dp[len])
            dp[++len] = b[i];
        else
        {
            int l = 1,r = len,mid,ans;
            while(l <= r)
            {
                mid = l + r >> 1;
                if(dp[mid] >= b[i])
                    ans = mid,r = mid - 1;
                else
                    l = mid + 1;
            }
            dp[ans] = b[i];
        }
    }
    printf("%d",len);
    return 0;
}