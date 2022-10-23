#include <cstdio>
#include <queue>
using namespace std;
const int maxn = 5e3 + 100,maxm = 5e4 + 100;
struct node
{
    int to,next,cap,cost;
}E[maxm<<1];
int head[maxn],tot = 1;
inline void add(const int &x,const int &y,const int &cap,const int &cost)
{
    E[++tot].next = head[x],head[x] = tot,E[tot].to = y,E[tot].cap = cap,E[tot].cost = cost;
}
const int inf = 1<<30;
int n,m,s,t;
int cur[maxn],dis[maxn],vis[maxn];
bool BFS()
{
    for (int i = 1; i <= n; ++i) dis[i] = inf,vis[i] = 0;
    queue<int> q;
    q.push(s), dis[s] = 0, cur[s] = head[s];
    while (!q.empty())
    {
        int u = q.front();
        q.pop(), vis[u] = 0;
        for (int p = head[u], v; p; p = E[p].next)
            if (E[p].cap && dis[v = E[p].to] > dis[u] + E[p].cost)
            {
                dis[v] = dis[u] + E[p].cost;
                if (!vis[v]) q.push(v), vis[v] = 1, cur[v] = head[v];
            }
    }
    return dis[t] != inf;
}
int sumcost;
int dfs(int u,int flow)
{
    if(u == t || !flow) return flow;
    vis[u] = 1;
    int sumflow = 0;
    for (int &p = cur[u],v,vflow; p; p = E[p].next)
    {
        if (!vis[v = E[p].to] && E[p].cap && dis[v] == dis[u] + E[p].cost && (vflow = dfs(v, min(flow, E[p].cap))))
        {
            E[p].cap -= vflow, E[p ^ 1].cap += vflow;
            flow -= vflow, sumflow += vflow, sumcost += vflow * E[p].cost;
            if (!flow) break;
        }
    }
    vis[u] = 0;
    return sumflow;
}
int main()
{
    scanf("%d %d %d %d",&n,&m,&s,&t);
    for (int i = 1, a, b, c, d; i <= m; ++i) scanf("%d %d %d %d", &a, &b, &c, &d), add(a, b, c, d), add(b, a, 0, -d);
    int sumflow = 0;
    while(BFS()) sumflow += dfs(s,inf);
    printf("%d %d\n",sumflow,sumcost);
    return 0;
}