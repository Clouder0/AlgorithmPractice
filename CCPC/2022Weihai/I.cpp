#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
const int maxn = 1e6 + 100;
#define int long long
int T, n, k, a[maxn], nowa[maxn], b[maxn], now[maxn];
bool check(int num)
{
    for (int i = 0; i < k; ++i)
        now[i] = b[i];
    for (int i = 1; i <= n; ++i) nowa[i] = num * a[i];
    for (int i = k - 1; i >= 0; --i)
    {
        if(!now[i]) continue;
        priority_queue<pair<int,int> > q;
        for (int j = 1; j <= n; ++j)
        {
            if (nowa[j] < (1 << i))
                q.push(make_pair(nowa[j], j));
            else 
            {
                int need = nowa[j] / (1 << i);
                if (need <= now[i])
                {
                    nowa[j] -= need * (1 << i);
                    now[i] -= need;
                    if(nowa[j]) q.push(make_pair(nowa[j],j));
                }
                else
                {
                    nowa[j] -= now[i] * (1 << i);
                    now[i] = 0;
                    break;
                }
            }
        }
        if (!q.empty() && now[i])
        {
            while (now[i] && !q.empty())
            {
                int t = q.top().second;
                --now[i], nowa[t] = 0;
                q.pop();
            }
        }
    }
    for (int i = 1; i <= n; ++i) if (nowa[i]) return 0;
    return 1;
}
signed main()
{
    scanf("%lld",&T);
    while(T--)
    {
        scanf("%lld%lld", &n, &k);
        long long sum = 0;
        long long sumd = 0;
        for (int i = 1; i <= n; ++i)
            scanf("%lld", a + i),sum += a[i];
        for (int i = 0; i < k; ++i)
            scanf("%lld", b + i),sumd += (1 << i) * b[i];
        int l = 1, r = sumd / sum + 4, mid, ans = 0;
        while(l <= r)
        {
            mid = (l + r) >> 1;
            if (check(mid))
                ans = mid, l = mid + 1;
            else
                r = mid - 1;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
