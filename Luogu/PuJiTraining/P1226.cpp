#include <cstdio>
using namespace std;
int b, mod;
long long a,t;
int main()
{
    scanf("%lld %d %d", &a, &b, &mod);
    printf("%lld^%d mod %d=",a,b,mod);
    for (t = a,a = 1; b; t = t * t % mod, b >>= 1)
        if (b & 1)
            a = a * t % mod;
    printf("%lld",a % mod);
    return 0;
}