# Solution

# Pre

很容易发现，$limit$是可以二分的，问题就转化成了经过若干个特定点的最短路问题。   
对于这种问题，可以先预处理出特定点的全图最短路，将特定点称为**中间点集**。  
无论是怎样的路线，都可以抽象为：

起点->中间点集->终点

中间点集内部的最短路就可以转化为旅行商问题。即求经过中间点集的所有点的最小距离。  
旅行商问题当然也有多种解法……  

# 全排列
可以用全排列来枚举中间点集的访问顺序，在访问完最后一个点后加上该点到终点的距离。  
具体可以使用深搜实现。
~~~cpp
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
~~~
## 时间复杂度分析

首先最外层的二分，复杂度为$O(\log max(weight))$。  
随后检验进行了$k+1$次最短路操作，复杂度为$O(kn\log n)$。  
跑出来最短路后枚举全排列，复杂度为$O(k!)$。  
综上所述，复杂度为$O(\log weight (k! + kn\log n))$。
即$O(\log weight \times k!)$。  
计算得出$\log weight$是$17$左右，$k!$最大达到$3628800$，那么最后复杂度已经不可接受了。  

## Code

~~~cpp
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
template <typename T>
inline void read(T &r)
{
    static char c;
    r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar());
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar());
}
const int maxm = 1e5 + 10;
const int maxn = 1e4 + 10;
const int maxk = 11;
const int INF = 1 << 30;
struct node
{
    int to, next, val, weight;
    node() {}
    node(const int &_to, const int &_next, const int &_val, const int &_weight) : to(_to), next(_next), val(_val), weight(_weight) {}
} E[maxm];
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
~~~

# 状压dp


解决旅行商问题的另一种办法就是状压dp。  
用二进制位的01来代表该点是否访问过，另开一维来代表最后访问的一个点。  
这里采用了dfs更新状态的方法，即枚举状态和起点，发现可行状态起点就dfs转移一次。  
dfs函数中选取终点，判断终点状态进行更优转移，再往下dfs。  
最后答案就是所有点都访问完、停在任意点的状态加上该点到终点的距离。

~~~cpp
inline void dfs(int u, int status)
{
    if (status == maxs)
        return;
    //选取下一个去往的点
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
        f[i][1 << (i - 1)] = dis[0][pos[i]]; //初始化为该点到起点距离

    for (int s = 1; s <= maxs; ++s)
        for (int i = 1; i <= k; ++i)
            if (f[i][s] != INF)
                dfs(i, s);

    for (int i = 1; i <= k; ++i)
    {
        f[i][maxs] += dis[i][t]; //加上到终点的距离
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
~~~

## 时间复杂度分析 

外层二分、中层最短路不再赘述了。  
相对于全排列的$O(n!)$枚举所有顺序，我们这里使用了状压dfs的方式。  
观察dp过程，可以发现每个点的状态最多被更新$k \times maxs$次，即任意起点任意状态到达该点都可能进行一次更新。  
而dfs过程中的更新，因为要保证$f[u][status] + dis[u][pos[v]] < f[v][status | (1 << (v - 1))]$即更优条件，并不会重复更新。  
那么复杂度就是$O(2^k \times k^2)$，算出来仅有$102400$之大，看起来是绰绰有余。

## Code

~~~cpp
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
template <typename T>
inline T _min(const T &a, const T &b) { return a < b ? a : b; }
template <typename T>
inline void read(T &r)
{
    static char c;r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar());
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar());
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
} E[maxm];
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
int f[maxk][1 << maxk];
int maxs;
int ans;
inline void dfs(int u, int status)
{
    if (status == maxs)
        return;
    //选取下一个去往的点
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
        f[i][1 << (i - 1)] = dis[0][pos[i]]; //初始化为该点到起点距离

    for (int s = 1; s <= maxs; ++s)
        for (int i = 1; i <= k; ++i)
            if (f[i][s] != INF)
                dfs(i, s);

    for (int i = 1; i <= k; ++i)
    {
        f[i][maxs] += dis[i][t]; //加上到终点的距离
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
    dij(s, limit, 0);
    for (int i = 1; i <= k; ++i)
        dij(pos[i], limit, i);
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
~~~

# Final

当然了，由于最短路也要占用时间，并且也不少，其实最后时间如何的确是非常玄学……  