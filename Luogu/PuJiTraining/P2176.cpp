#include <cstdio>
#include <memory.h>
#include <queue>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxm = 1e4 + 100;
const int maxn = 110;
struct node
{
    int to, next, val;
    node() {}
    node(const int &_to, const int &_next, const int &_val) : to(_to), next(_next), val(_val) {}
} E[maxm];
int head[maxn];
int tot;
inline void add(const int &x, const int &y, const int &val)
{
    E[++tot] = node(y, head[x], val), head[x] = tot;
}
int n, m;
int dis[maxn], pre[maxn], vis[maxn];
priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > q;
int sx, sy;
inline void dij()
{
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    dis[1] = 0;
    q.push(make_pair(0, 1));
    int u, v;
    while (!q.empty())
    {
        u = q.top().second;
        q.pop();
        if (vis[u])
            continue;
        vis[u] = 1;
        for (int p = head[u]; p; p = E[p].next)
        {
            v = E[p].to;
            if ((u == sx && v == sy) || (u == sy && v == sx))
            {
                if (!vis[v] && dis[v] > dis[u] + 2 * E[p].val)
                {
                    dis[v] = dis[u] + E[p].val * 2;
                    pre[v] = u;
                    q.push(make_pair(dis[v], v));
                }
                continue;
            }
            if (!vis[v] && dis[v] > dis[u] + E[p].val)
            {
                dis[v] = dis[u] + E[p].val;
                pre[v] = u;
                q.push(make_pair(dis[v], v));
            }
        }
    }
}
int X[maxm], Y[maxm], cnt;
int main()
{
    read(n);
    read(m);
    int a, b, c;
    for (int i = 1; i <= m; ++i)
    {
        read(a);
        read(b);
        read(c);
        add(a, b, c);
        add(b, a, c);
    }
    dij();
    int u, v = n;
    while (v != 1)
    {
        u = pre[v];
        X[++cnt] = u;
        Y[cnt] = v;
        v = u;
    }
    int od = dis[n];
    int ans = 0;
    for (int i = 1; i <= cnt; ++i)
    {
        sx = X[i], sy = Y[i];
        dij();
        if (dis[n] - od > ans)
            ans = dis[n] - od;
    }
    printf("%d", ans);
    return 0;
}