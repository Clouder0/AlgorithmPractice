#include <cstdio>
#include <algorithm>
#define int long long
template<typename T> inline T min(const T &a,const T &b){return a<b?a:b;}
const int maxn = 510,maxm = 11000;
struct node
{
    int to,next,cap;
}E[maxm<<1];
int head[maxn],tot = 1;
inline void add(const int &x,const int &y,const int &cap)
{
    E[++tot].next = head[x],head[x] = tot,E[tot].to = y,E[tot].cap = cap;
}
int n,m,x;
int cur[maxn],q[maxn],dep[maxn],qt,qh;
bool bfs()
{
    for (int i = 1; i <= n; ++i) dep[i] = 0;
    dep[1] = 1,qh = 1,q[qt = 1] = 1,cur[1] = head[1];
    while(qt >= qh)
    {
        int u = q[qh++];
        if(u == n) return 1;
        for (int p = head[u],v; p; p = E[p].next)
            if(E[p].cap && !dep[v = E[p].to]) dep[v] = dep[u] + 1,q[++qt] = v,cur[v] = head[v];
    }
    return 0;
}
int dfs(int u,int flow)
{
    if(u == n || !flow) return flow;
    int sumflow = 0;
    for (int &p = cur[u], v, vflow; p; p = E[p].next)
    {
        if (dep[v = E[p].to] == dep[u] + 1 && E[p].cap && (vflow = dfs(v, min(E[p].cap, flow))))
        {
            E[p].cap -= vflow, E[p ^ 1].cap += vflow, sumflow += vflow, flow -= vflow;
            if (!flow) break;
        }
    }
    return sumflow;
}
signed main()
{
    scanf("%lld %lld %lld",&n,&m,&x);
    for (int i = 1,a,b,c; i <= m; ++i) scanf("%lld %lld %lld",&a,&b,&c),add(a,b,c),add(b,a,0);
    int ans = 0;
    while (bfs()) ans += dfs(1, 1ll << 60);
    if (!ans) puts("Orz Ni Jinan Saint Cow!");
    else printf("%lld %lld\n", ans, std::max(1ll, (x + ans - 1) / ans));
    return 0;
}