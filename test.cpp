#include <cstdio>
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
inline long long getC(long long y)
{
    while(y % 2 == 0)
        y /= 2;
    while(y % 5 == 0)
        y /= 5;
    return y;
}
long long n,ans;
int main()
{
    read(n);
    for(int y = 1;y<=n;++y)
        ans += n / getC(y);
    printf("%lld",ans);
    return 0;
}