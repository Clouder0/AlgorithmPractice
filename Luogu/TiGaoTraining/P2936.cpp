#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1000, maxm = 5200;
struct node
{
    int to, next, cap;
} E[maxm];
int head[maxn], tot = 1;
inline void add(const int& x, const int& y, const int& cap)
{
    E[++tot].next = head[x], head[x] = tot, E[tot].to = y, E[tot].cap = cap;
}
int n, m, s, t;
int dep[maxn], q[maxn], qt, qh, cur[maxn];
inline bool bfs()
{
    for (int i = 1; i <= 100; ++i) dep[i] = 0;
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
    scanf("%d",&n);
    s = 1,t = 26;
    for (int i = 1,x; i <= n; ++i) 
    {
        char s1[5],s2[5];
        scanf("%s %s %d",s1 + 1,s2 + 1,&x);
        s1[1] = s1[1] - 'A' + 1,s2[1] = s2[1] - 'A' + 1;
        add(s1[1],s2[1],x),add(s2[1],s1[1],0);
    }
    int ans = 0;
    while(bfs()) ans += dfs(s,1<<30);
    printf("%d\n",ans);
    return 0;
}