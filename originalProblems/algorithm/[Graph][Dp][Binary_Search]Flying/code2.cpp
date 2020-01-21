//DFS + DIJ
#pragma GCC optimize(2)
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
inline char nc()
{
	static char buf[1000000],*p1 = buf,*p2 = buf;
	return p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1000000,stdin),p1 == p2) ? EOF : *p1++;
}
template <typename T>
inline void read(T &r)
{
    static char c;
    r = 0;
    for (c = nc(); c > '9' || c < '0'; c = nc());
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = nc());
}
const int maxm = 1e5 + 10;
const int maxn = 1e4 + 10;
const int maxk = 11;
const int INF = 1061109567;
struct node
{
    int to, next, val, weight;
    node() {}
    node(const int &_to, const int &_next, const int &_val, const int &_weight) : to(_to), next(_next), val(_val), weight(_weight) {}
} E[maxm<<1];
int head[maxn];
inline void add(const int &x, const int &y, const int &val, const int &weight)
{
    static int tot = 0;
    E[++tot] = node(y, head[x], val, weight), head[x] = tot;
}
int n, m, k, s, t;
int maxweight, tempdis, ansdis;
int pos[maxk];
int dis[maxk][maxn];
bool vis[maxn];
priority_queue<pair<int, int> > q;
inline void dij(const int &start, const int &limit, const int &num)
{
    memset(vis, 0, sizeof(vis));
    memset(dis[num], 0x3f, sizeof(dis[num]));
    dis[num][start] = 0;
    q.push(make_pair(0, start));
    int u, v;
    while (!q.empty())
    {
        u = q.top().second;
        q.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        for (int p = head[u]; p; p = E[p].next)
        {
            v = E[p].to;
            if (vis[v] || E[p].weight > limit || E[p].val + dis[num][u] > dis[num][v])
                continue;
            dis[num][v] = E[p].val + dis[num][u];
            q.push(make_pair(-dis[num][v], v));
        }
    }
}
bool visk[maxk];
inline void dfs(int dep, int u, int nowsum)
{
    if (nowsum > tempdis)
        return;
    if (dep == k)
    {
        nowsum += dis[u][t];
        tempdis = tempdis > nowsum ? nowsum : tempdis;
        return;
    }
    for (int i = 1; i <= k; ++i)
    {
        if (visk[i])
            continue;
        visk[i] = true;
        dfs(dep + 1, i, nowsum + dis[u][pos[i]]);
        visk[i] = false;
    }
}
inline bool check(const int &limit)
{
    memset(visk,0,sizeof(visk));
    dij(s, limit, 0);
    for (int i = 1; i <= k; ++i)
        dij(pos[i], limit, i);
    tempdis = INF;
    dfs(0, 0, 0);
    if (tempdis != INF)
    {
        ansdis = tempdis;
        return true;
    }
    else
        return false;
}
inline void solve()
{
    ansdis = INF;
    int ll = 0, rr = maxweight, mid, limit = -1;
    while (ll <= rr)
    {
        mid = (ll + rr) >> 1;
        if (check(mid))
        {
            rr = mid - 1;
            limit = mid;
        }
        else
            ll = mid + 1;
    }
    if(limit == -1)
        printf("-1");
    else
        printf("%d %d", limit, ansdis);
}
int main()
{
    read(n);
    read(m);
    read(k);
    read(s);
    read(t);
    for (int i = 1; i <= k; ++i)
        read(pos[i]);
    int x, y, dis, weight;
    for (int i = 1; i <= m; ++i)
    {
        read(x);
        read(y);
        read(dis);
        read(weight);
        if (weight > maxweight)
            maxweight = weight;
        add(x, y, dis, weight);
        add(y, x, dis, weight);
    }
    solve();
    return 0;
}
/*
Example 1:

Input
3 3 1 1 3
2
1 2 2 10
2 3 4 10
1 3 3 10
Output
10 6

Example 2:

Input
3 3 3 1 3
1 2 3
1 2 2 10
2 3 4 20
1 3 3 10
Output
10 7

Example 3:

Input
3 1 3 1 3
1 2 3
1 3 3 10
Output
-1

*/
