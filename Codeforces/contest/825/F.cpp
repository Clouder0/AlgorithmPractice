#include <cstdio>
#include <queue>
#include <algorithm>

#define int long long

const int maxn = 2e5 + 100, maxm = 4e5 + 100;

int cnt, ver[maxm], head[maxn], net[maxm], w[maxm];
void add(int x, int y, int z) {
    ver[++cnt] = y, net[cnt] = head[x], head[x] = cnt; w[cnt] = z;
}


int n, m, dis[maxn], vis[maxn];

signed main () {
    scanf("%lld%lld", &n, &m);
    for (int i = 1; i <= m; ++i) {
        int x, y, z;
        scanf("%lld%lld%lld", &x, &y, &z);
        z = 2 * z;
        add(x, y, z);
        add(y, x, z);
    }
    for (int i = 1; i <= n; i++) scanf("%lld", &dis[i]);
    std::priority_queue<std::pair<int, int> > q;
    for (int i = 1; i <= n; ++i) q.push(std::make_pair(-dis[i], i));
    while(!q.empty()) {
        int x = q.top().second; q.pop();
        if(vis[x]) continue;
        vis[x] = 1;
        for (int i = head[x]; i; i = net[i]) {
            int y = ver[i], z = w[i];
            if(!vis[y] && dis[y] > dis[x] + z) {;
                dis[y] = dis[x] + z;
                q.push(std::make_pair(-dis[y], y));
            }
        }
    }
    for (int i = 1; i <= n; i++) printf("%lld ", dis[i]);
    return 0;
}