#include <cstdio>
#define int long long

int exgcd(int a, int b, int& x, int& y)
{
    if (b == 0) return x = 1, y = 0, a;
    int ret = exgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return ret;
}

bool linearEquation(int a, int& x, int b, int& y, int c)
{
    int g = exgcd(a, b, x, y);
    if (c % g) return false;
    int scale = c / g;
    x = x * scale;
    y = y * scale;
    // x minimum positive root
    int mod = b / g;
    x = x % mod;
    if (x <= 0) x += mod;
    y = (c - a * x) / b;
    return true;
}

int LinearModEquation(int a, int& x, int b, int p)
{
    int y;
    linearEquation(a, x, p, y, b);
    return x % p;
}

int a, b;
signed main()
{
    scanf("%lld%lld",&a,&b);
    int x, y;
    linearEquation(a, x, b, y, 1);
    printf("%lld\n", x);
    return 0;
}
