#include <cstdio>
const int maxn = 1e5 + 100;
struct node
{
    int to, next;
} E[maxn << 1];
int head[maxn],tot;
inline void add(int x, int y) { E[++tot].next = head[x], head[x] = tot, E[tot].to = y; }
int n, k, t, fa[maxn], vis[maxn];
int q[maxn],qt,qh;
void dfs(int u,int left,int from)
{
    vis[u] = 1;
    if(!left) return;
    for (int p = head[u]; p; p = E[p].next) if(E[p].to != from) dfs(E[p].to,left - 1,u);
}
int main()
{ 
    scanf("%d %d %d",&n,&k,&t);
    for (int i = 1, a, b; i < n; ++i) scanf("%d %d", &a, &b), add(a, b), add(b, a);
    qt = qh = 1, q[1] = 1;
    while (qt >= qh)
    {
        int u = q[qh++];
        for (int p = head[u], v; p; p = E[p].next) if ((v = E[p].to) != fa[u]) fa[v] = u, q[++qt] = v;
    }
    int ans = 0;
    for (int i = n; i; --i) if (!vis[q[i]]) 
    {
        ++ans;
        int x = q[i];
        for (int j = 1; j <= k; ++j) x = fa[x];
        dfs(x, k,0);
    }
    printf("%d\n",ans);
    return 0;
}