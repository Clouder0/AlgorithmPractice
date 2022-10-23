#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1e4,maxm = 2e4 + 100;
struct node
{
    int to,next,cap;
}E[maxm];
int head[maxn],tot = 1;
inline void add(const int &x,const int &y,const int &c)
{
    E[++tot].next = head[x],head[x] = tot,E[tot].to = y,E[tot].cap = c;
}
int n,m,s,t,P,Q;
int q[maxn],qt,qh,dep[maxn],cur[maxn];
inline bool bfs()
{
    for (int i = 0; i <= n * 2 + P + Q + 1; ++i)  dep[i] = 0;
    cur[s] = head[s],dep[s] = 1,qh = 1,q[qt = 1] = s;
    while(qt >= qh)
    {
        int u = q[qh++];
        if(u == t) return 1;
        for (int p = head[u],v; p; p = E[p].next)
            if (E[p].cap && !dep[v = E[p].to]) dep[v] = dep[u] + 1, cur[v] = head[v], q[++qt] = v;
    }
    return 0;
}
int dfs(int u,int flow)
{
    if(u == t || !flow) return flow;
    int sumflow = 0;
    for (int &p = cur[u], vflow; p; p = E[p].next)
    {
        int v = E[p].to;
        if(E[p].cap && dep[v] == dep[u] + 1 && (vflow = dfs(v,min(flow,E[p].cap))))
        {
            E[p].cap -= vflow,E[p^1].cap += vflow,flow -= vflow,sumflow += vflow;
            if(!flow) break;
        }
    }
    return sumflow;
}
int main()
{
    scanf("%d %d %d",&n,&P,&Q);
    s = 0, t = n * 2 + P + Q + 1;
    for (int i = 1; i <= n; ++i) add(P + i, P + i + n, 1), add(P + i + n, P + i, 0);
    for (int i = 1; i <= P; ++i) add(s, i, 1), add(i, s, 0);
    for (int i = 1; i <= Q; ++i) add(P + 2 * n + i, t, 1), add(t, P + 2 * n + i, 0);
    for (int i = 1; i <= n; ++i)
        for (int j = 1, x; j <= P; ++j)
        {
            scanf("%d", &x);
            if (x) add(j, P + i, 1), add(P + i, j, 0);
        }
    for (int i = 1; i <= n; ++i)
        for (int j = 1, x; j <= P; ++j)
        {
            scanf("%d", &x);
            if (x) add(P + n + i, P + 2 * n + j, 1), add(P + 2 * n + j, P + n + i, 0);
        }
    
    int res = 0;
    while(bfs()) res += dfs(s,1<<30);
    printf("%d\n",res);
    return 0;
}