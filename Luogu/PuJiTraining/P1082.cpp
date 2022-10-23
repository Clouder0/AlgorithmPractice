#include <cstdio>
long long a,b;
inline void exgcd(long long a,long long b,long long &x,long long &y)
{
    if (b == 0) return (void)(x = 1, y = 0);
    exgcd(b, a % b, y, x), y -= x * (a / b);
}
int main()
{
    scanf("%lld %lld",&a,&b);
    long long x,y;
    if(a > b) exgcd(a,b,x,y); else exgcd(b,a,y,x);
    x = ((x % b) + b) % b;
    printf("%lld\n",x);
    return 0;
}