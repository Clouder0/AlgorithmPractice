//DP + DIJ + kruskal
#pragma GCC optimize(2)
#include <cstdio>
#include <cstring>
#include <algorithm>
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
const int maxm = 1e6 + 10;
const int maxn = 1e5 + 10;
const int maxk = 11;
const long long INF = 4557430888798830399;
const int inf = 1061109567;
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
    E[++tot] = node(x, head[y], val, weight), head[y] = tot;
}
struct edge
{
    int from,to,val,weight;
    edge(){}
    edge(const int &_from, const int &_to, const int &_val, const int &_weight) : from(_from), val(_val), weight(_weight) {}
    bool operator<(const edge &b) const
    {
        return this->weight < b.weight;
    }
} edges[maxm];
int n, m, k, s, t;
int pos[maxk];
long long dis[maxk][maxn];
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
int fa[maxn];
int rnk[maxn];
inline int find(const int &x)
{
    return  fa[x] == x ? x : fa[x] = find(fa[x]);
}
inline void unite(const int &x,const int &y)
{
    int a = find(x),b = find(y);
    if(a == b)
        return;
    if(rnk[a] == rnk[b])
        fa[a] = b,++rnk[b];
    else if(rnk[a] > rnk[b])
        fa[b] = a;
    else
        fa[a] = b;
}
inline bool checkConnected()
{
    int f = find(s);
    for(int i = 1;i<=k;++i)
        if(f != find(pos[i]))
            return false;
    return f == find(t);
}
inline int kruskal()
{
    int lim = inf;
    edge *p;
    for(int i = 1;i <= n;++i)
        fa[i] = i;
    sort(edges+1,edges+1+m);
    for(p = edges+1;p <= edges+1+m;++p)
    {
        add(p->from,p->to,p->val,p->weight);
        unite(p->from,p->to);
        if(checkConnected())
        {
            lim = p->weight;
            break;
        }
    }
    for(++p;p->weight <= lim && p <= edges + 1 + m;++p)
        add(p->from,p->to,p->val,p->weight);
    return lim;
}
long long f[maxk][1 << maxk];
long long ans;
int maxs;
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
inline long long dp()
{
    long long ans = INF;
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
        ans = _min(ans, f[i][maxs]);
    }
    return ans;
}
inline long long getDis(const int &limit)
{
    SPFA(s, limit, 0);
    for (int i = 1; i <= k; ++i)
        SPFA(pos[i], limit, i);
    return dp();
}
inline void solve()
{
    int lim = kruskal();
    if(lim == inf)
    {
        printf("-1");
        return;
    }
    printf("%d %lld",lim,getDis(lim));
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
        read(edges[i].from);
        read(edges[i].to);
        read(edges[i].val);
        read(edges[i].weight);
    }
    solve();
    return 0;
}