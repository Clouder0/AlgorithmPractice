#include <cstdio>

const int maxn = 1e5 + 100;
struct node
{
    int to, next;
} E[maxn];
int head[maxn], cnt;
inline void add(const int& u, const int& v)
{
    E[++cnt].next = head[u], head[u] = cnt, E[cnt].to = v;
}

int n, m;

namespace Topo
{
int in[maxn], q[maxn], qh, qt;
void TopoSort()
{
    for (int i = 1; i <= n; ++i) in[i] = 0;
    for (int u = 1; u <= n; ++u)
        for (int p = head[u]; p; p = E[p].next) ++in[E[p].to];
    qh = 1, qt = 0;
    for (int i = 1; i <= n; ++i)
        if (!in[i]) q[++qt] = i;
    while (qh >= qt)
    {
        int u = q[qh++];
        for (int p = head[u]; p; p = E[p].next)
        {
            int v = E[p].to;
            if (--in[v] == 0)
                q[++qt] = v;
        }
    }
}
}  // namespace Topo