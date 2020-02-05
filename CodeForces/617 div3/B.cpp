#include <cstdio>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
long long n,T;
int main()
{
    read(T);
    while(T--)
    {
        read(n);
        long long ans = n;
        while(n >= 10)
        {
            ans += n / 10;
            n = (n / 10) + (n % 10);
        }
        printf("%lld\n",ans);
    }
    return 0;
}