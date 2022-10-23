#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
const int maxn = 1e6 + 100;
#define int long long
int n, up[maxn], down[maxn], left[maxn], right[maxn];
int X[maxn], Y[maxn];
int H[maxn], hcnt;
vector<int> vy[maxn];
int sum[maxn], vis[maxn], num[maxn];
inline void add(int x, int k)
{
    for (; x <= hcnt; x += x & -x) sum[x] += k;
}
inline int ask(int x)
{
    int res = 0;
    for (; x > 0; x -= x & -x) res += sum[x];
    return res;
}
signed main()
{
    scanf("%lld", &n);
    for (int i = 1, x, y; i <= n; ++i) scanf("%lld %lld", X + i, Y + i), H[++hcnt] = X[i], H[++hcnt] = Y[i];
    sort(H + 1, H + 1 + hcnt), hcnt = unique(H + 1, H + 1 + hcnt) - H - 1;
    for (int i = 1; i <= n; ++i) X[i] = lower_bound(H + 1, H + 1 + hcnt, X[i]) - H;
    for (int i = 1; i <= n; ++i) Y[i] = lower_bound(H + 1, H + 1 + hcnt, Y[i]) - H;
    for (int i = 1; i <= n; ++i) vy[Y[i]].push_back(X[i]), num[X[i]]++;
    for (int i = 1; i <= hcnt; ++i) sort(vy[i].begin(), vy[i].end());
    long long res = n;
    for (int i = 0; i <= hcnt; ++i)
    {
        for (vector<int>::iterator it = vy[i].begin(); it != vy[i].end(); ++it)
            if (num[*it] > 1 && vis[*it]) add(*it, -1), --num[*it], vis[*it] = 0;
        for (int j = 0; j < (int)vy[i].size() - 1; ++j)
            if (vy[i][j + 1] - 1 > vy[i][j]) res += ask(vy[i][j + 1] - 1) - ask(vy[i][j]);
        for (vector<int>::iterator it = vy[i].begin(); it != vy[i].end(); ++it)
            if (num[*it] > 1 && !vis[*it]) add(*it, 1), vis[*it] = 1;
    }
    printf("%lld\n", res);
    return 0;
}
