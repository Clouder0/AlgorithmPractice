#include <cstdio>
#include <algorithm>
#include <map>
using namespace std;
#define int long long
const int maxn = 5e6 + 100;
const int INF =  1ll << 60;
int T, n, k, a[maxn], x[maxn], y[maxn];
map<int, int> lim;
map<int, int> num;
signed main()
{
    scanf("%lld",&T);
    while(T--)
    {
        scanf("%lld%lld", &n, &k);
        lim.clear(), num.clear();
        for (int i = 1; i <= n; ++i) scanf("%lld", a + i), num[a[i]]++;
        for (int i = 1; i <= k; ++i) scanf("%lld %lld", x + i, y + i), lim[x[i]] = y[i];
        lim[-1] = 0;
        lim[1e9 + 1] = 0;
        std::sort(a + 1, a + 1 + n);
        int p = 0;
        long long res = 0;
        auto l = lim.begin(), r = lim.begin();
        while(r != lim.end())
        {
            r = l, ++r;
            while(r != lim.end() && r->second != 0) ++r;
            // (l,r)
            ++l;
            while(l != r)
            {
                
            }
        }
        if (res & 1) puts("Pico");
        else puts("FuuFuu");
    }
    return 0;
}