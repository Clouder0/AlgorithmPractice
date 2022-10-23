#include <cstdio>
#include <algorithm>
#include <cstring>
#define int long long
const int maxn = 100100;
const int maxm = maxn * 2;
struct node
{
    int to,next,val;
}E[maxm];
int head[maxn];
inline void add(const int &x,const int &y,const int &val)
{
    static int tot = 0;
    E[++tot].next = head[x], E[tot].to = y, E[tot].val = val, head[x] = tot;
}
int n,root;
int f[maxn],dis[maxn];
void dfs(int u,int fa)
{
    for (int p = head[u],v; p; p = E[p].next)
        if ((v = E[p].to) != fa) dis[v] = dis[u] + E[p].val, dfs(v, u);
}
void dp(int u,int fa)
{   
    int t = 0,flag = 0;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa) continue;
        dp(v, u), t += f[v], flag = 1;
    }
    if (!flag) f[u] = dis[u] - dis[fa];
    else f[u] = std::min(dis[u] - dis[fa], t);
}
signed main()
{
    scanf("%lld %lld", &n, &root);
    if(n == 1) {puts("0");return 0;}
    for (int i = 1, a, b, c; i < n; ++i)
        scanf("%lld %lld %lld", &a, &b, &c), add(a, b, c), add(b, a, c);
    for (int i = 1; i <= n; ++i) f[i] = 1<<29;
    dis[0] = -(1 << 29);
    dfs(root, 0);
    dp(root, 0);
    printf("%lld\n",f[root]);
    return 0;
}