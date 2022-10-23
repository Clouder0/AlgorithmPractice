#include <cstdio>
#include <algorithm>
using namespace std;
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
int cnt,n, m, s, t;
int dep[maxn], q[maxn], qt, qh, cur[maxn];
inline bool bfs()
{
    for (int i = 1; i <= cnt; ++i) dep[i] = 0;
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
int k;
int lid[110],rid[110];
int L[110],C[110],cantL[110],cantC[110];
int A[110][110];
int main()
{
    scanf("%d %d %d",&n,&m,&k);
    s = ++cnt,t = ++cnt;
    int res = n * m;
    for (int i = 1; i <= n; ++i) scanf("%d", L + i),L[i] = L[i],lid[i] = ++cnt;
    for (int i = 1; i <= m; ++i) scanf("%d", C + i),C[i] = C[i],rid[i] = ++cnt;
    for (int i = 1,a,b; i <= k; ++i) scanf("%d %d",&a,&b),A[a][b] = 1,cantL[a]++,cantC[b]++,--res;
    for (int i = 1; i <= n; ++i) if (L[i] > m - cantL[i]) { puts("JIONG!"); return 0; }
    for (int i = 1; i <= m; ++i) if (C[i] > n - cantC[i]) { puts("JIONG!"); return 0; }
    for (int i = 1; i <= n; ++i) add(s,lid[i],m - cantL[i] - L[i]),add(lid[i],s,0);
    for (int i = 1; i <= m; ++i) add(rid[i],t,n - cantC[i] - C[i]),add(t,rid[i],0);
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) if(!A[i][j])
        add(lid[i], rid[j], 1), add(rid[j], lid[i], 0);
    while (bfs()) res -= dfs(s, 1 << 30);
    printf("%d\n",res);
    return 0;
}