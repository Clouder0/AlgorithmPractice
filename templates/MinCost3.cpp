#include <algorithm>
#include <cstdio>
#include <queue>
using namespace std;
const int maxn = 1e4 + 100, maxm = 1e5 + 100;
struct node
{
    int to, next, cost, cap;
} E[maxm];
int head[maxn];
inline void add(int x, int y, int cap, int cost)
{
    static int tot = 1;
    E[++tot].next = head[x], head[x] = tot, E[tot].to = y, E[tot].cap = cap, E[tot].cost = cost;
    E[++tot].next = head[y], head[y] = tot, E[tot].to = x, E[tot].cap = 0, E[tot].cost = -cost;
}
int n, m, s, t, costsum;
int dis[maxn], inq[maxn], cur[maxn];
bool spfa()
{
    for (int i = 1; i <= n; ++i) dis[i] = 1 << 30, inq[i] = 0, cur[i] = head[i];
    queue<int> q;
    q.push(s), dis[s] = 0;
    while (q.size())
    {
        int u = q.front();
        q.pop(), inq[u] = 0;
        for (int p = head[u]; p; p = E[p].next)
        {
            int v = E[p].to;
            if (E[p].cap && dis[v] > dis[u] + E[p].cost)
            {
                dis[v] = dis[u] + E[p].cost;
                if (!inq[v]) inq[v] = 1, q.push(v);
            }
        }
    }
    return dis[t] != (1 << 30);
}
int ins[maxn];
int dfs(int u, int flow)
{
    if (u == t || !flow) return flow;
    int sumflow = 0, vflow = 0;
    ins[u] = 1;
    for (int& p = cur[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (!ins[v] && E[p].cap && dis[v] == dis[u] + E[p].cost && (vflow = dfs(v, min(flow, E[p].cap))))
        {
            E[p].cap -= vflow, E[p ^ 1].cap += vflow, costsum += vflow * E[p].cost, sumflow += vflow, flow -= vflow;
            if (!flow) break;
        }
    }
    ins[u] = 0;
    return sumflow;
}
int main()
{
    scanf("%d %d %d %d", &n, &m, &s, &t);
    for (int i = 1, u, v, w, c; i <= m; ++i) scanf("%d %d %d %d", &u, &v, &w, &c), add(u, v, w, c);
    int res = 0;
    while (spfa())
        res += dfs(s, 1 << 30);
    printf("%d %d\n", res, costsum);
    return 0;
}
