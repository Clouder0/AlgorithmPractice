#include <cstdio>
#include <algorithm>
using namespace std;
#define int long long
int T,n,sum,maxx;
signed main()
{
    scanf("%lld",&T);
    while(T--)
    {
        scanf("%lld", &n);
        sum = maxx = 0;
        for (int i = 1, a, b; i <= n; ++i)
        {
            scanf("%lld%lld", &a, &b);
            if (a < b) std::swap(a, b);
            maxx = std::max(maxx, a), sum += b;
        }
        printf("%lld\n", 2 * maxx + 2 * sum);
    }
    return 0;
}