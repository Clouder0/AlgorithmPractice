#include <cstdio>
#include <algorithm>
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
int T;
long long x,y;
inline long long gcd(long long a,long long b)
{
    return b == 0 ? a : gcd(b,a % b);
}
int main()
{
    read(T);
    for(int i = 1;i<=T;++i)
    {
        read(x),read(y);
        if(x < y) std::swap(x,y);
        printf("Case %d: %lld\n",i,x / gcd(x,y) * y);
    }
}