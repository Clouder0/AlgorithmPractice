#include <cstdio>
using namespace std;
template<typename T>
inline T _max(const T &a,const T &b){return a>b?a:b;}
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 3e5 + 10;
int T,n;
long long a[maxn],b[maxn],c[maxn];
int main()
{
    read(T);
    while(T--)
    {
        read(n);
        for(int i = 1;i<=n;++i)
            read(a[i]),read(b[i]);
        long long sum = 0;
        for(int i = 2;i<=n;++i)
            sum += (c[i] = _max(a[i] - b[i-1],0ll));
        sum += (c[1] = _max(a[1] - b[n],0ll));
        int minn = 1;
        long long ans = 1ll << 60;
        for(int i = 1;i<=n;++i)
        {
            long long ret = sum - c[i] + a[i];
            if(ret < ans)
                ans = ret;
        }
        printf("%lld\n",ans);
    }
    return 0;
}