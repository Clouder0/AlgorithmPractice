#include <cstdio>
#include <algorithm>
#define int long long
const int maxn = 1e5;
struct node
{
    int to, next;
} E[maxn];
int head[maxn], cnt;
inline void add(const int& u, const int& v)
{
    E[++cnt].next = head[u], head[u] = cnt, E[cnt].to = v;
}
int n, fa[maxn], f[maxn][2];
void dfs(int u)
{
    f[u][0] = 1;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa[u]) continue;
        fa[v] = u, dfs(v);
        f[u][0] += std::min(f[v][0],f[v][1]);
        f[u][1] += f[v][0];
    }
}
signed main()
{
    while(~scanf("%lld", &n))
    {
        for (int i = 1; i <= n; ++i)
            fa[i] = head[i] = f[i][0] = f[i][1] = 0;
        cnt = 0;
        for (int i = 1; i <= n; ++i)
        {
            int u, v, num;
            scanf("%lld:(%lld)", &u, &num);
            ++u;
            while (num--) scanf("%lld", &v), ++v, add(u, v), add(v, u);
        }
        dfs(1);
        printf("%lld\n", std::min(f[1][0], f[1][1]));
    }
    return 0;
}