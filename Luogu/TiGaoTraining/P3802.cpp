#include <cstdio>
using namespace std;
long long a[10];
int main()
{
    long long n = 0;
    for (int i = 1; i <= 7; ++i) scanf("%lld", a + i), n += a[i];
    double ans = 7 * 6 * 5 * 4 * 3 * 2 * 1 * (n - 6);
    if(n <= 6) 
    {
        puts("0.000");
        return 0;
    }
    for (int i = 1; i <= 7; ++i) ans = ans / (n - i + 1) * a[i];
    printf("%.3f", ans);
    return 0;
}