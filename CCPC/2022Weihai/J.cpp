#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 5e6 + 100;
#define int long long
const int INF = 1ll << 60;
int T, n, k, a[maxn], H[maxn], cnt;
int X[maxn], Y[maxn];
int num[maxn], lim[maxn];
int sum, res;

void work(int l, int r)
{
    if(l > r) return;
    long long num_sum = 0;
    for (int i = l; i <= r; ++i) num_sum += num[i];
    for (int i = l; i <= r; ++i)
    {
        if(num_sum >= lim[i])
        {
            num_sum -= lim[i];
            res += H[i] * lim[i];
        }
        else
        {
            res += H[i] * num_sum;
            num_sum = 0;
            return;
        }
    }
}

signed main()
{
    scanf("%lld",&T);
    while(T--)
    {
        scanf("%lld%lld", &n, &k);
        cnt = 0; sum = 0; res = 0;
        H[++cnt] = 0;
        for (int i = 1; i <= n; ++i)
            scanf("%lld", a + i), H[++cnt] = a[i], sum += a[i], H[++cnt] = a[i] + 1;
        for (int i = 1; i <= k; ++i)
            scanf("%lld%lld", X + i, Y + i), H[++cnt] = X[i], H[++cnt] = X[i] + 1;
        sort(H + 1, H + 1 + cnt), cnt = unique(H + 1, H + 1 + cnt) - H - 1;
        for (int i = 1; i <= n; ++i)
            a[i] = lower_bound(H + 1, H + 1 + cnt, a[i]) - H;
        for (int i = 1; i <= k; ++i)
            X[i] = lower_bound(H + 1, H + 1 + cnt, X[i]) - H;
        for (int i = 1; i <= cnt; ++i)
            num[i] = 0;
        for (int i = 1; i <= n; ++i)
            num[a[i]]++;
        for (int i = 1; i <= cnt; ++i) lim[i] = INF;
        for (int i = 1; i <= k; ++i)
            lim[X[i]] = Y[i];
        for (int l = 1, r; l <= cnt;)
        {
            if (lim[l] == 0)
            {
                res += H[l] * num[l];
                ++l;
                continue;
            }
            r = l;
            while (lim[r + 1] != 0 && r + 1 <= cnt)
                ++r;
            work(l, r);
            l = r + 1;
        }
        if ((sum - res) & 1)
            puts("Pico");
        else
            puts("FuuFuu");
    }
    return 0;
}
