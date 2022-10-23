#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
const int maxn = 1e5, maxm = 1e7;
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
    for (int i = 1; i <= 2 * n + 2; ++i) dep[i] = 0;
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
            if (!vflow) dep[v] = 0;
            if (!flow) break;
        }
    return sumflow;
}
vector<int> id1[7], id2[7];
int l1[maxn], l2[maxn];
int main()
{
    scanf("%d %d", &n, &m);
    s = 2 * n + 1, t = 2 * n + 2;
    for (int i = 1; i <= n; ++i)
    {
        char s[10];
        scanf("%s", s + 1);
        if (s[1] == 'J') id1[1].push_back(i);
        else if (s[1] == 'H') id1[2].push_back(i);
        else if (s[1] == 'W') id1[3].push_back(i);
        else if (s[1] == 'Y') id1[4].push_back(i);
        else if (s[1] == 'E') id1[5].push_back(i);
    }
    for (int i = 1; i <= n; ++i)
    {
        char s[10];
        scanf("%s", s + 1);
        if (s[1] == 'J') id2[1].push_back(i);
        else if (s[1] == 'H') id2[2].push_back(i);
        else if (s[1] == 'W') id2[3].push_back(i);
        else if (s[1] == 'Y') id2[4].push_back(i);
        else if (s[1] == 'E') id2[5].push_back(i);
    }

    for (int i = 1; i <= n; ++i) scanf("%d", l1 + i);
    for (int i = 1; i <= n; ++i) scanf("%d", l2 + i);
    for (vector<int>::iterator it = id1[1].begin(); it != id1[1].end(); ++it) l1[*it] += id1[4].size();
    for (vector<int>::iterator it = id2[1].begin(); it != id2[1].end(); ++it) l2[*it] += id2[4].size();
    for (int i = 1; i <= n; ++i) add(s, i, l1[i]), add(i, s, 0);
    for (int i = 1; i <= n; ++i) add(n + i, t, l2[i]), add(t, n + i, 0);
    for (vector<int>::iterator it = id1[1].begin(); it != id1[1].end(); ++it)
    {
        for (vector<int>::iterator it2 = id2[2].begin(); it2 != id2[2].end(); ++it2)
            add(*it, n + *it2, 1), add(n + *it2, *it, 0);
        for (vector<int>::iterator it2 = id2[3].begin(); it2 != id2[3].end(); ++it2)
            add(*it, n + *it2, 1), add(n + *it2, *it, 0);
    }
    for (vector<int>::iterator it = id1[2].begin(); it != id1[2].end(); ++it)
    {
        for (vector<int>::iterator it2 = id2[3].begin(); it2 != id2[3].end(); ++it2)
            add(*it, n + *it2, 1), add(n + *it2, *it, 0);
        for (vector<int>::iterator it2 = id2[5].begin(); it2 != id2[5].end(); ++it2)
            add(*it, n + *it2, 1), add(n + *it2, *it, 0);
    }
    for (vector<int>::iterator it = id1[3].begin(); it != id1[3].end(); ++it)
    {
        for (vector<int>::iterator it2 = id2[4].begin(); it2 != id2[4].end(); ++it2)
            add(*it, n + *it2, 1), add(n + *it2, *it, 0);
        for (vector<int>::iterator it2 = id2[5].begin(); it2 != id2[5].end(); ++it2)
            add(*it, n + *it2, 1), add(n + *it2, *it, 0);
    }
    for (vector<int>::iterator it = id1[4].begin(); it != id1[4].end(); ++it)
    {
        for (vector<int>::iterator it2 = id2[1].begin(); it2 != id2[1].end(); ++it2)
            add(*it, n + *it2, 1), add(n + *it2, *it, 0);
        for (vector<int>::iterator it2 = id2[2].begin(); it2 != id2[2].end(); ++it2)
            add(*it, n + *it2, 1), add(n + *it2, *it, 0);
    }
    for (vector<int>::iterator it = id1[5].begin(); it != id1[5].end(); ++it)
    {
        for (vector<int>::iterator it2 = id2[1].begin(); it2 != id2[1].end(); ++it2)
            add(*it, n + *it2, 1), add(n + *it2, *it, 0);
        for (vector<int>::iterator it2 = id2[4].begin(); it2 != id2[4].end(); ++it2)
            add(*it, n + *it2, 1), add(n + *it2, *it, 0);
    }
    int res = 0, left = m, t;
    while (bfs() && (t = dfs(s, left))) res += t, left -= t;
    printf("%d\n", res);
    return 0;
}