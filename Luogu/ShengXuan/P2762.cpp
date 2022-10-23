#include <cstdio>
#include <sstream>
#include <iostream>
using namespace std;
const int bufSize = 1e6;
const int maxn = 1e5, maxm = 1e6;
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
    for (int i = 1; i <= m + n + 2; ++i) dep[i] = 0;
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
const int inf = 1<<30;
int main()
{
    cin >> m >> n;
    s = m + n + 1,t = m + n + 2;
    int sum = 0;
    getchar();
    for (int i = 1, x; i <= m; ++i)
    {
        string S;
        getline(cin,S);
        stringstream st(S);
        st >> x;
        add(s,i,x),add(i,s,0),sum += x;
        while(st >> x) add(i,m + x,inf),add(m + x,i,0);
    }
    for (int i = 1, x; i <= n; ++i) cin >> x, add(m + i, t, x), add(t, m + i, 0);
    int res = 0;
    while(bfs()) res += dfs(s,inf);
    for (int i = 1; i <= m; ++i)  if(dep[i]) printf("%d ",i);
    puts("");
    for (int i = 1; i <= n; ++i)  if(dep[m + i]) printf("%d ",i);
    puts("");
    printf("%d\n",sum - res);
    return 0;
}