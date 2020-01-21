#include <cstdio>
#include <cstring>
#include <queue>
#define debug
inline char nc()
{
#ifdef debug
    return getchar();
#endif
    static char buf[100000], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
}
template <typename T>
inline void read(T &r)
{
    static char c;r = 0;
    for (c = nc(); c > '9' || c < '0'; c = nc());
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = nc());
}
template <typename T>
inline T min(const T &a, const T &b) { return a < b ? a : b; }
const int maxm = 2100000;
int next[maxm], to[maxm], val[maxm];
int head[2100];
inline void add(const int &x, const int &y, const int &_val)
{
    static int tot = 1;
    next[++tot] = head[x];
    to[tot] = y;
    val[tot] = _val;
    head[x] = tot;
}
inline bool bfs();
int dfs(int u, int flow);
void dinic();
int n, m, e;
int main()
{
    read(n);
    read(m);
    read(e);
    //编号：1为源点，[2,n+1]为左半边，[n+2,n+m+1]为右半边，n+m+2为汇点
    for (int i = 1; i <= n; ++i)
    {
        add(1, i + 1, 1);
        add(i + 1, 1, 0);
    }
    for (int i = 1; i <= m; ++i)
    {
        add(n + 1 + i, n + m + 2, 1);
        add(n + m + 2, n + 1 + i, 0);
    }
    int u, v;
    for (; e; --e)
    {
        read(u);
        read(v);
        if (v > m || u > n)
            continue;
        add(u + 1, v + n + 1, 1);
        add(v + n + 1, u + 1, 0);
    }
    dinic();
    return 0;
}
int dep[2100], cur[2100];
inline bool bfs()
{
    std::queue<int> q;
    memset(dep, 0, sizeof(dep));
    dep[1] = 1;
    q.push(1);
    int u;
    while (!q.empty())
    {
        u = q.front();
        q.pop();
        if (u == n + m + 2)
            return true;
        for (int p = head[u]; p; p = next[p])
            if (val[p] && !dep[to[p]])
            {
                dep[to[p]] = dep[u] + 1;
                q.push(to[p]);
            }
    }
    return dep[n + m + 2];
}
int dfs(int u, int flow)
{
    if (!flow || u == n + m + 2)
        return flow;
    int ans(0), temp;
    for (int &p = cur[u]; p; p = next[p])
        if (dep[u] + 1 == dep[to[p]] && val[p] && (temp = dfs(to[p], min(flow, val[p]))))
        {
            ans += temp;
            val[p] -= temp;
            val[p ^ 1] += temp;
            if (!(flow -= temp))
                break;
        }
    return ans;
}
void dinic()
{
    int ans = 0, temp;
    while (bfs())
    {
        for (int i = n + m + 2; i; --i)
            cur[i] = head[i];
        while ((temp = dfs(1, 999999)))
            ans += temp;
    }
    printf("%d", ans);
}