#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
#define int long long
typedef long long ll;
const int maxn = 5e5 + 100;
const ll INF = 1e18;
const ll LARGE = 1e12;
int n, m, S, T;
struct node
{
    int from, to, next;
    ll cap, cost, raw_cap;
}E[maxn];
int head[maxn], tot = 1;
int vis[maxn], pre[maxn];
ll dis[maxn], p[maxn];
priority_queue<pair<ll, int>> q;
inline void _add(int u, int v, ll f, ll w)
{
    E[++tot].from = u, E[tot].to = v, E[tot].next = head[u], head[u] = tot;
    E[tot].raw_cap = f, E[tot].cost = w;
    E[tot].cap = 0;
}
void add(int u, int v, ll f, ll w) { _add(u, v, f, w), _add(v, u, 0, -w); }
ll c(int id) { return E[id].cost + p[E[id].from] - p[E[id].to]; }
void Dijkstra(int s)
{
    for (int i = 1; i <= n + 2; ++i) vis[i] = 0, dis[i] = INF, pre[i] = -1;
    dis[s] = 0;
    q.push({-dis[s], s});
    while (!q.empty())
    {
        int u = q.top().second;
        q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for(int p = head[u];p;p=E[p].next)
        {
            int v = E[p].to;
            if (E[p].cap && dis[v] > dis[u] + c(p))
            {
                dis[v] = dis[u] + c(p);
                pre[v] = p;
                q.push({-dis[v], v});
            }
        }
    }
}
void add_one_cap(int id)
{
    int u = E[id].from, v = E[id].to;
    if (E[id].cap)
    {
        ++E[id].cap;
        return;
    }
    Dijkstra(v);
    if (dis[u] < INF && dis[u] + c(id) < 0)
    {
        ++E[id ^ 1].cap;
        while (u != v)
        {
            int x = pre[u];
            --E[x].cap;
            ++E[x ^ 1].cap;
            u = E[x].from;
        }
    }
    else ++E[id].cap;
    ll max_dis = 0;
    ll cur_len = c(id);
    for (int i = 1; i <= n; ++i)
        if (dis[i] < INF) max_dis = max(max_dis, dis[i]);
    for (int i = 1; i <= n; ++i) p[i] += dis[i] < INF ? dis[i] : max_dis + max(0ll, -cur_len);
    Dijkstra(n + 1);
    for (int i = 1; i <= n; ++i) p[i] += dis[i];
}
void init()
{
    for (int i = 1; i <= n + 2; ++i) head[i] = p[i] = 0;
    tot = 1;
}
void run()
{
    add(T, S, LARGE, -LARGE);
    int st_id = tot - 1;  // the cap of rev edge of t->s indicates the flow of (t->s), which is exactly the max flow.
    for (int i = 1; i <= n; ++i) add(n + 1, i, 0, 0), E[tot - 1].cap = 1;
    for (int i = 40; i >= 0; --i)
    {
        for (int j = 2; j <= tot; ++j) E[j].cap <<= 1;
        for (int j = 2; j <= tot; j += 2)
            if ((E[j].raw_cap >> i) & 1) add_one_cap(j);
    }
    ll min_cost = 0;
    for (int j = 1; j <= m; ++j)
        min_cost += E[j << 1].cost * E[(j << 1) | 1].cap;
    ll max_flow = E[st_id ^ 1].cap;
    printf("%lld %lld", max_flow, min_cost);
}
signed main()
{
    scanf("%lld%lld%lld%lld", &n, &m, &S, &T);
    init();
    for (int i = 1; i <= m; ++i) 
    {
        int u, v, f, w;
        scanf("%lld%lld%lld%lld", &u, &v, &f, &w);
        add(u, v, f, w);
    }
    run();
    return 0;
}