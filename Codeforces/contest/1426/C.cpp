#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
#define int long long
int T,n;
signed main()
{
    scanf("%lld",&T);
    while(T--)
    {
        scanf("%lld",&n);
        int sn = max(1ll,(int)floor(sqrt(n)) - 20);
        int tp = max(sn,(int)(ceil(sqrt(n))) + 20);
        int minn = 1ll<<60;
        for (int i = sn; i <= tp; ++i) minn = min(minn, (n - 1) / i + i - 1);
        printf("%lld\n", minn);
    }
    return 0;
}