#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1e4, maxm = 1e5;
struct node
{
    int to, next, cap;
} E[maxm];
int head[maxn], tot = 1;
inline void add(const int& x, const int& y, const int& cap)
{
    E[++tot].next = head[x], head[x] = tot, E[tot].to = y, E[tot].cap = cap;
}
int k,n, m, s, t;
int dep[maxn], q[maxn], qt, qh, cur[maxn];
inline bool bfs()
{
    for (int i = 0; i <= n + k + 1; ++i) dep[i] = 0;
    dep[s] = 1, cur[s] = head[s], qh = 1, q[qt = 1] = s;
    while (qt >= qh)
    {
        int u = q[qh++];
        if (u == t) return 1;
        for (int p = head[u], v; p; p = E[p].next)
            if (E[p].cap && !dep[v = E[p].to]) dep[v] = dep[u] + 1, cur[v] = head[v], q[++qt] = v;
    }
    return 0;
}
int dfs(int u, int flow)
{
    if (u == t || !flow) return flow;
    int sumflow = 0;
    for (int &p = cur[u], v, vflow; p; p = E[p].next)
        if (dep[v = E[p].to] == dep[u] + 1 && (vflow = dfs(v, min(E[p].cap, flow))))
        {
            flow -= vflow, sumflow += vflow, E[p].cap -= vflow, E[p ^ 1].cap += vflow;
            if(!vflow) dep[v] = 0;
            if (!flow) break;
        }
    return sumflow;
}
int main()
{
    scanf("%d %d",&k,&n);
    s = 0,t = n + k + 1;
    int sum = 0;
    for (int i = 1, x; i <= k; ++i) scanf("%d", &x), add(s, i, x), add(i, s, 0),sum += x;
    for (int i = 1; i <= n; ++i) add(k + i,t,1),add(t,k + i,0);
    for (int i = 1,num,x; i <= n; ++i) 
    {
        scanf("%d",&num);
        while (num--) scanf("%d", &x), add(x, k + i, 1), add(k + i, x, 0);
    }
    int res = 0;
    while (bfs()) res += dfs(s, 1 << 30);
    if(res != sum) puts("No Solution!");
    else
    {
        for(int u = 1;u<=k;++u)
        {
            printf("%d: ", u);
            for (int p = head[u]; p; p = E[p].next)
            {
                int v = E[p].to;
                if(!E[p].cap && v > k) printf("%d ",v - k);
            }
            puts("");
        }
    }
    return 0;
}