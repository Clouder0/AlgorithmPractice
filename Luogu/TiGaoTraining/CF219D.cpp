#include <algorithm>
#include <cstdio>
using namespace std;
const int maxn = 1e6 + 100;
int n;
struct node
{
    int to, val, next;
} E[maxn];
int head[maxn];
inline void add(int x, int y, int z)
{
    static int tot = 0;
    E[++tot].to = y, E[tot].next = head[x], head[x] = tot, E[tot].val = z;
}
int dis[maxn], f[maxn], dep[maxn];
void dfs(int u, int fa)
{
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa) continue;
        dep[v] = dep[u] + 1, dis[v] = dis[u] + E[p].val, dfs(v, u), f[u] += f[v] + E[p].val;
    }
}
int main()
{
    scanf("%d", &n);
    for (int i = 1, u, v; i < n; ++i) scanf("%d %d", &u, &v), add(u, v, 0), add(v, u, 1);
    dfs(1, 0);
    int minn = f[1];
    for (int i = 2; i <= n; ++i) minn = min(minn, f[1] - dis[i] + dep[i] - dis[i]);
    printf("%d\n", minn);
    for (int i = 1; i <= n; ++i)
        if (f[1] + dep[i] - 2 * dis[i] == minn) printf("%d ", i);
    return 0;
}
