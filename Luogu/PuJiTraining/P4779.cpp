#include <cstdio>
#include <queue>
const int maxn = 4e5 + 10;
const int inf = 1 << 30;
struct node
{
    int to, next, val;
} E[maxn];
int head[maxn], cnt;
inline void add(int u, int v, int w)
{
    E[++cnt].next = head[u], head[u] = cnt, E[cnt].to = v, E[cnt].val = w;
}
int n,m,s;
int dis[maxn], vis[maxn];
void dij()
{
    for (int i = 1; i <= n; ++i) dis[i] = inf;
    std::priority_queue<std::pair<int,int>,std::vector<std::pair<int,int>>,std::greater<std::pair<int,int>>> q;
    dis[s] = 0,q.push(std::make_pair(0,s));
    while(!q.empty())
    {
        int u = q.top().second;
        q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (int p = head[u]; p; p = E[p].next)
        {
            int v = E[p].to;
            if (dis[v] > dis[u] + E[p].val) dis[v] = dis[u] + E[p].val, q.push(std::make_pair(dis[v], v));
        }
    }
}
int main()
{
    scanf("%d%d%d",&n,&m,&s);
    for (int i = 1; i <= m; ++i) 
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c), add(a, b, c);
    }
    dij();
    for (int i = 1; i <= n; ++i) printf("%d ",dis[i]);
    return 0;
}