#include <cstdio>
#include <algorithm>
const int maxn = 1e5 + 10;
const int maxm = 1e5 + 10;
struct node
{
    int v, next;
} E[maxm];
int head[maxn], cnt;
inline void add(int u, int v)
{
    E[++cnt].next = head[u];
    E[cnt].v = v;
    head[u] = cnt;
}
int maxx[maxn], vis[maxn];
void dfs(int u)
{
    vis[u] = 1;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].v;
        if (!vis[v]) maxx[v] = std::max(maxx[v], maxx[u]), dfs(v);
    }
}
int n, m;
int main()
{
    scanf("%d %d", &n, &m);
    for (int i = 1, u, v; i <= m; ++i)
    {
        scanf("%d%d", &u, &v);
        add(v, u);
    }
    for (int i = 1; i <= n; ++i) maxx[i] = i;
    for (int i = n; i; --i)
        if(!vis[i]) dfs(i);
    for (int i = 1; i <= n; ++i) printf("%d ", maxx[i]);
    return 0;
}