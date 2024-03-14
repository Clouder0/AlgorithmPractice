#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 5100;
const int maxm = 1e5 + 100;
int n, a[maxn];
int odd[maxn], ocnt, even[maxn], ecnt;
namespace Dinic
{
int n, m, S, T;
struct node
{
    int to, next, val;
} E[maxm];
int cur[maxn], head[maxn], tot = 1;
inline void _add(const int& x, const int& y, const int& v)
{
    E[++tot].to = y, E[tot].next = head[x], E[tot].val = v, head[x] = tot;
}
inline void add(int x, int y, int v) { _add(x, y, v), _add(y, x, 0); }
int dep[maxn], q[maxn], qt, qh;
inline bool BFS()
{
    for (int i = 1; i <= n; ++i) dep[i] = 0;
    qh = 1, q[qt = 1] = S, cur[S] = head[S], dep[S] = 1;
    while (qt >= qh)
    {
        int u = q[qh++];
        if (u == T) return 1;
        for (int p = head[u], v; p; p = E[p].next)
            if (E[p].val && !dep[v = E[p].to])
                cur[v] = head[v], dep[v] = dep[u] + 1, q[++qt] = v;
    }
    return 0;
}
long long dfs(int u, long long flow)
{
    if (u == T || !flow) return flow;
    long long sumflow = 0, vflow;
    for (int& p = cur[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (dep[v] == dep[u] + 1 && E[p].val && (vflow = dfs(v, min(flow, 1ll * E[p].val))) > 0)
        {
            E[p].val -= vflow, E[p ^ 1].val += vflow, sumflow += vflow, flow -= vflow;
            if (flow == 0) break;
        }
    }
    return sumflow;
}
void init()
{
    for (int i = 1; i <= n; ++i) head[i] = 0;
    tot = 1;
}
long long Dinic()
{
    long long ans = 0;
    while (BFS()) ans += dfs(S, 1ll << 60);
    return ans;
}
}  // namespace Dinic

bool isPrime(int x)
{
    for (int i = 2; i * i <= x; ++i)
        if (x % i == 0) return 0;
    return 1;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    for (int i = 1; i <= n; ++i)
        if (a[i] & 1)
            odd[++ocnt] = a[i];
        else
            even[++ecnt] = a[i];
    namespace d = Dinic;
    d::n = n + 2, d::S = n + 1, d::T = n + 2;
    for (int i = 1; i <= ocnt; ++i)
        for (int j = 1; j <= ecnt; ++j)
            if (isPrime(odd[i] + even[i])) d::add(i, j + ocnt, 1);
    for (int i = 1; i <= ocnt; ++i) d::add(d::S, i, 1);
    for (int j = 1; j <= ecnt; ++j) d::add(j + ocnt, d::T, 1);
    printf("%lld\n", d::Dinic());
    return 0;
}