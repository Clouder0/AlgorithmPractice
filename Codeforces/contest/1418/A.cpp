#include <cstdio>
int T;
long long x,y,k;
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%lld %lld %lld",&x,&y,&k);
        long long need = k * y + k - 1;
        printf("%lld\n",(x - 2 + need) / (x - 1) + k);
    }
    return 0;
}