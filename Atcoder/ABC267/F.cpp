#include <cstdio>
#include <queue>
#include <map>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
#define DEBUG
inline char nc()
{
    #ifdef DEBUG
    return getchar();
    #endif
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
inline void read(char *s)
{
    static char c;
    for (; !isalpha(c); c = nc());
    for (; isalpha(c); c = nc()) *s++ = c;
    *s = '\0';
}
template<typename T>
inline T read(T &r)
{
    static char c;
    static int flag;
    flag = 1, r = 0;
    for (c = nc(); !isdigit(c); c = nc()) if (c == '-') flag = -1;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r *= flag;
}
const int maxn = 2e5 + 100;
struct node
{
    int to, next;
} E[2 * maxn];
int head[maxn];
inline void add(const int &x,const int &y)
{
    static int tot = 0;
    E[++tot].next = head[x],E[tot].to = y,head[x] = tot;
}
struct query
{
    int u, k;
} Q[maxn];
int n, m, fa[maxn], dep[maxn], maxdep[maxn], ans[maxn];
std::vector<int> qb[maxn];
std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> V[maxn];
std::map<int,int> dep2id[maxn];
void dfs(int u)
{
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa[u]) continue;
        dep[v] = dep[u] + 1, fa[v] = u, dfs(v);
    }
}
void dfs2(int u)
{
    dep2id[u][dep[u]] = u;
    maxdep[u] = dep[u];
    for(int p = head[u];p;p=E[p].next)
    {
        int v = E[p].to;
        if(v == fa[u]) continue;
        dfs2(v);
        while(!V[v].empty() && V[v].top().first <= maxdep[u] - 2 * dep[u])
        {
            ans[V[v].top().second] = dep2id[u][V[v].top().first + 2 * dep[u]];
            V[v].pop();
        }
        while(!V[u].empty() && V[u].top().first <= maxdep[v] - 2 * dep[u])
        {
            ans[V[u].top().second] = dep2id[v][V[u].top().first + 2 * dep[u]];
            V[u].pop();
        }
        if (V[u].size() < V[v].size()) std::swap(V[u], V[v]);
        while (!V[v].empty()) V[u].push(V[v].top()), V[v].pop();
        maxdep[u] = std::max(maxdep[u], maxdep[v]);
        if (dep2id[u].size() < dep2id[v].size()) std::swap(dep2id[u], dep2id[v]);
        dep2id[u].merge(dep2id[v]);
    }
    for (std::vector<int>::iterator it = qb[u].begin(); it != qb[u].end(); ++it)
        if (maxdep[u] - dep[u] >= Q[*it].k)
            ans[*it] = dep2id[u][dep[u] + Q[*it].k];
        else
            V[u].push(std::make_pair(Q[*it].k - dep[u], *it));
}
int main()
{
    read(n);
    for (int i = 1, a, b; i < n; ++i) read(a), read(b), add(a, b), add(b, a);
    read(m);
    for (int i = 1; i <= m; ++i) read(Q[i].u), read(Q[i].k), qb[Q[i].u].push_back(i);
    dep[1] = 1, dfs(1);
    dfs2(1);
    for (int i = 1; i <= m; ++i) printf("%d\n",ans[i] > 0 ? ans[i] : -1);
    return 0;
}