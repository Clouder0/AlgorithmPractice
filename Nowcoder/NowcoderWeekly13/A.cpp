#include <cstdio>
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
int n;
long long ans;
int main()
{
    read(n);
    int minn = 1<<30;
    for(int i = 1;i<=n;++i)
    {
        int x;
        read(x);
        ans += x;
        if(minn > x) minn = x;
    }
    ans += 1ll * minn * n - 2*minn;
    printf("%lld",ans);
    return 0;
}