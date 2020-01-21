//DP + SPFA
#pragma GCC optimize(2)
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
template <typename T>
inline T _min(const T &a, const T &b) { return a < b ? a : b; }
inline char nc()
{
    static char buf[1000000],*p1 = buf,*p2 = buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
}
template <typename T>
inline void read(T &r)
{
    static char c;r = 0;
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
int maxweight;
int pos[maxk];
int dis[maxk][maxn];
bool inq[maxn];
//About SPFA,it's dead.
queue<int> q;
inline void SPFA(const int &start,const int &limit,const int &num)
{
    memset(inq, 0, sizeof(inq));
    memset(dis[num], 0x3f, sizeof(dis[num]));
    dis[num][start] = 0;
    q.push(start);
    int u, v;
    while (!q.empty())
    {
        u = q.front();
        q.pop();
        inq[u] = false;
        for (int p = head[u]; p; p = E[p].next)
        {
            v = E[p].to;
            if (E[p].weight > limit || E[p].val + dis[num][u] >= dis[num][v])
                continue;
            dis[num][v] = E[p].val + dis[num][u];
            if(inq[v])
                continue;
            inq[v] = true;
            q.push(v);
        }
    }
}
int f[maxk][1 << maxk];
int maxs;
int ans;
inline void dfs(int u, int status)
{
    if (status == maxs)
        return;
    for (int v = 1; v <= k; ++v)
    {
        if (u != v && (status & (1 << (v - 1))) == 0 && f[u][status] + dis[u][pos[v]] < f[v][status | (1 << (v - 1))])
        {
            f[v][status | (1 << (v - 1))] = f[u][status] + dis[u][pos[v]];
            dfs(v, status | (1 << (v - 1)));
        }
    }
}
inline bool dp()
{
    int temp = INF;
    maxs = (1 << k) - 1;
    memset(f, 0x3f, sizeof(f));
    for (int i = 1; i <= k; ++i)
        f[i][1 << (i - 1)] = dis[0][pos[i]];

    for (int s = 1; s <= maxs; ++s)
        for (int i = 1; i <= k; ++i)
            if (f[i][s] != INF)
                dfs(i, s);

    for (int i = 1; i <= k; ++i)
    {
        f[i][maxs] += dis[i][t]; 
        temp = _min(temp, f[i][maxs]);
    }
    if (temp == INF)
        return false;
    else
    {
        ans = temp;
        return true;
    }
}
inline bool check(const int &limit)
{
    SPFA(s, limit, 0);
    for (int i = 1; i <= k; ++i)
        SPFA(pos[i], limit, i);
    return dp();
}
inline void solve()
{
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
    if (limit == -1)
        printf("-1");
    else
        printf("%d %d", limit, ans);
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