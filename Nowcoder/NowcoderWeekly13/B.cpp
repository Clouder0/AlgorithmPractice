#include <cstdio>
const int maxn = 1e5 + 100;
template <typename T>
void read(T &r)
{
    static char c;
    r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar());
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar());
}
struct node
{
    int to, next;
} E[maxn << 1];
int head[maxn];
inline void add(const int &x, const int &y)
{
    static int tot = 0;
    E[++tot].next = head[x], head[x] = tot, E[tot].to = y;
}
int n, m;
int size[maxn];
int dp[maxn],dep[maxn];
void pre(int u,int fa)
{
    size[u] = 1;
    for(int p = head[u];p;p=E[p].next)
    {
        int v = E[p].to;
        if(v == fa) continue;
        dep[v] = dep[u] + 1,pre(v,u);
        size[u] += size[v];
    }
}
void dfs(int u,int fa)
{
    dp[u] = dp[fa] + n - size[u] * 2;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(v == fa) continue;
        dfs(v,u);
    }
}
int main()
{
    read(n), read(m);
    for (int i = 1; i <= m; ++i)
    {
        int x, y;
        read(x), read(y);
        add(x, y), add(y, x);
    }
    pre(1,0);
    for(int i = 2;i<=n;++i) dp[1] += dep[i];
    for(int p = head[1];p;p=E[p].next)
    {
        int v = E[p].to;
        if(v == 1) continue;
        dfs(v,1);
    }
    int ans = 1<<30;
    for(int i = 1;i<=n;++i) if(ans > dp[i]) ans = dp[i];
    for(int i = 1;i<=n;++i) if(ans == dp[i]) printf("%d ",i);
    return 0;
}