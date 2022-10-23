#include <cstdio>
#include <queue>
#include <cstring>
#define int long long
using namespace std;
template <typename T>
void read(T &r)
{
    static char c;
    r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar());
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar());
}
const int maxn = 200;
const int maxm = 150;
struct node
{
    int to, next, val;
} E[maxm << 2];
int head[maxm];
inline void add(const int &x, const int &y, const int &val)
{
    static int t = 0;
    E[++t].to = y;
    E[t].next = head[x];
    E[t].val = val;
    head[x] = t;
}
int n, m, k, e;
int cost[maxn][maxn];
int f[maxn];
std::priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > q;
int cant[maxm], oc[maxn][maxm];
inline int dij()
{
    int dis[maxm], vis[maxm];
    memset(vis, 0, sizeof(vis));
    q.push(make_pair(0, 1));
    dis[1] = 0;
    for (int i = 2; i <= m; ++i)
        dis[i] = 1ll << 50;
    int u, v;
    while (!q.empty())
    {
        u = q.top().second;
        q.pop();
        if (vis[u])
            continue;
        vis[u] = 1;
        for (int p = head[u]; p; p = E[p].next)
        {
            v = E[p].to;
            if (vis[v] || cant[v])
                continue;
            if (dis[v] > dis[u] + E[p].val)
                dis[v] = dis[u] + E[p].val, q.push(make_pair(dis[v], v));
        }
    }
    return dis[m];
}
signed main()
{
    read(n);
    read(m);
    read(k);
    read(e);
    for (int i = 1; i <= e; ++i)
    {
        int u, v, d;
        read(u), read(v), read(d);
        add(u, v, d);
        add(v, u, d);
    }
    int d;
    read(d);
    for (int i = 1; i <= d; ++i)
    {
        int p, a, b;
        read(p), read(a), read(b);
        for (int j = a; j <= b; ++j)
            oc[j][p] = 1;
    }
    for (int i = 1; i <= n; ++i)
    {
        memset(cant, 0, sizeof(cant));
        for (int j = i; j <= n; ++j)
        {
            for (int k = 1; k <= m; ++k)
                if (oc[j][k])
                    cant[k] = 1;
            cost[i][j] = dij();
        }
    }
    for (int i = 1; i <= n; ++i)
        f[i] = cost[1][i] * i;
    for (int i = 1; i <= n; ++i)
        for (int j = i - 1; j > 0; --j)
        {
            if (f[i] > f[j] + cost[j + 1][i] * (i - j) + k)
                f[i] = f[j] + cost[j + 1][i] * (i - j) + k;
        }
    printf("%lld", f[n]);
    return 0;
}