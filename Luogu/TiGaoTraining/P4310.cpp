#include <cstdio>
template<typename T>
inline T max(const T &a,const T &b){return a>b?a:b;}
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 1e5 + 100;
int n;
int f[maxn];
int main()
{
    read(n);
    int x,ans = 0;
    for(int i = 1;i<=n;++i)
    {
        read(x);
        int t = 0;
        for(int k = 0;(1<<k) <= x;++k)
            if((1<<k) & x)
                t = max(f[k] + 1,t);
        for(int k = 0;(1<<k) <= x;++k)
            if((1<<k) & x)
                f[k] = max(f[k],t);
        ans = max(ans,t);
    }
    printf("%d",ans);
    return 0;
}