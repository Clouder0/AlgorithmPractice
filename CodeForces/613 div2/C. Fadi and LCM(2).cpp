#include <cstdio>
#include <algorithm>
using namespace std;
template <typename T>
void read(T &r)
{
    static char c;r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar());
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar());
}
long long x, a, b;
int main()
{
    read(x);
    for (long long i = 1; i * i <= x; ++i)
    {
        if (x % i)
            continue;
        if (__gcd(i, x / i) == 1)
            a = i, b = x / i;
    }
    printf("%lld %lld", a, b);
    return 0;
}