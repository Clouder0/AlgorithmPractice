#include <cstdio>
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
int T;
long long x;
int main()
{
    read(T);
    while(T--)
    {
        read(x);
        long long ans = 0;
        while(x % 6 == 0) ++ans, x /= 6;
        while(x % 3 == 0) ans += 2,x /= 3;
        if(x == 1) printf("%lld\n",ans);
        else puts("-1");
    }
    return 0;
}