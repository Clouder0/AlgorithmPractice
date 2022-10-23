#include <algorithm>
#include <cstdio>
const int maxn = 1e5 + 100;
struct node
{
    int to, next;
} E[maxn << 1];
int head[maxn], tot;
inline void add(const int& x, const int& y) { E[++tot].next = head[x], E[tot].to = y, head[x] = tot; }
int T, n;
int size[maxn], maxp[maxn], root1, root2;
void dfs(int u, int fa)
{
    maxp[u] = 0, size[u] = 1;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa) continue;
        dfs(v, u), size[u] += size[v];
        maxp[u] = std::max(maxp[u], size[v]);
    }
    maxp[u] = std::max(n - size[u], maxp[u]);
    if (maxp[u] < maxp[root1]) root1 = u, root2 = 0;
    else if (maxp[u] == maxp[root1]) root2 = u;
}
int isleaf[maxn], fat[maxn];
void dfs2(int u, int fa)
{
    fat[u] = fa, isleaf[u] = 1;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa) continue;
        dfs2(v, u), isleaf[u] = 0;
    }
}
int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d",&n);
        tot = 0;
        for (int i = 1; i <= n; ++i) isleaf[i] = 0, fat[i] = 0, head[i] = 0;
        int tx, ty;
        for (int i = 1, x, y; i < n; ++i) scanf("%d %d", &x, &y), add(x, y), add(y, x), tx = x, ty = y;
        root1 = 0, root2 = 0;
        maxp[0] = 1 << 30;
        dfs(1, 0);
        if (!root2)
        {
            printf("%d %d\n", tx, ty);
            printf("%d %d\n", tx, ty);
            goto end;
        }
        dfs2(root1, root2);
        for (int i = 1; i <= n; ++i)
            if (isleaf[i])
            {
                printf("%d %d\n", fat[i], i);
                printf("%d %d\n", i, root2);
                goto end;
            }
    end:;
    }
    return 0;
}