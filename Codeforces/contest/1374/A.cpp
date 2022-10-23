#include <cstdio>
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
int T;
long long x,y,n;
int main()
{
    read(T);
    while(T--)
    {
        read(x),read(y),read(n);
        long long p = (n / x) * x + y;
        while(p > n) p -= x;
        printf("%lld\n",p);
    }
    return 0;
}