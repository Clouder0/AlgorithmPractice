#include <algorithm>
#include <cstdio>
using namespace std;
const int maxn = 2e6 + 100;

struct node
{
    int to, next;
} E[maxn];
int head[maxn], cnt;
inline void add(const int& u, const int& v)
{
    E[++cnt].next = head[u], head[u] = cnt, E[cnt].to = v;
}

namespace Tarjan
{
int n;
int dfn[maxn], low[maxn], ind;
int ins[maxn], st[maxn], top;
int bel[maxn], sccnum;
void clear()
{
    ind = top = sccnum = 0;
    for (int i = 1; i <= n; ++i) dfn[i] = low[i] = ins[i] = bel[i] = 0;
}
void dfs(int u)
{
    dfn[u] = low[u] = ++ind;
    st[++top] = u, ins[u] = 1;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (!dfn[v])
            dfs(v), low[u] = min(low[u], low[v]);
        else if (ins[v])
            low[u] = min(low[u], dfn[v]);
    }
    if (low[u] == dfn[u])
    {
        ++sccnum;
        while (st[top] != u) bel[st[top]] = sccnum, ins[st[top--]] = 0;
        --top, bel[u] = sccnum, ins[u] = 0;
    }
}
}  // namespace Tarjan

namespace SAT
{
int n;
inline int rev(const int& x) { return x > n ? x - n : x + n; }
inline void conflict(const int& a, const int& b)
{
    // a and b can't be true at the same time
    add(a, rev(b)), add(b, rev(a));
}
int res[maxn];
bool check()
{
    // return True if possible and construct a solution
    // False otherwise.
    for (int i = 1; i <= 2 * n; ++i) res[i] = 0;
    Tarjan::n = 2 * n;
    Tarjan::clear();
    for (int i = 1; i <= 2 * n; ++i)
        if (!Tarjan::dfn[i]) Tarjan::dfs(i);
    for (int i = 1; i <= n; ++i)
        if (Tarjan::bel[i] == Tarjan::bel[i + n]) return false;
    for (int i = 1; i <= n; ++i)
        if (Tarjan::bel[i] < Tarjan::bel[i + n])
            res[i] = 1, res[i + n] = 0;
        else
            res[i] = 0, res[i + n] = 1;
    return true;
}
}  // namespace SAT

int n, m;
int main()
{
    scanf("%d%d", &n, &m);
    SAT::n = n;
    while (m--)
    {
        int i,a,j,b;
        scanf("%d%d%d%d", &i, &a, &j, &b);
        SAT::conflict(i + a * n, j + b * n);
    }
    if (!SAT::check())
    {
        puts("IMPOSSIBLE");
        return 0;
    }
    puts("POSSIBLE");
    for (int i = 1; i <= n; ++i)
        putchar(SAT::res[i] + '0'), putchar(' ');
    return 0;
}