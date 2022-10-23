#include <cstdio>
#include <algorithm>
#include <set>
#include <ctype.h>
#include <queue>
const int bufSize = 1e6;
using namespace std;
inline char nc()
{
    #ifdef DEBUG
    return getchar();
    #endif
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
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
const int maxn = 1100;
struct node
{
    int to, next, val;
} E[maxn << 1];
int head[maxn];
inline void add(const int &x,const int &y,const int &val)
{
    static int tot = 0;
    E[++tot].next = head[x],E[tot].to = y,E[tot].val = val,head[x] = tot;
}
int n, m, k;
set<int> S;
struct Query
{
    int u, v;
} Q[maxn];
int dis[maxn][maxn];
bool vis[maxn];
void dij(int s, int* dis)
{

    for (int i = 1; i <= n; ++i) dis[i] = 1 << 30,vis[i] = 0; 
    priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int > > > q;
    dis[s] = 0, q.push(make_pair(0, s));
    while (!q.empty())
    {
        int u = q.top().second;
        q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (int p = head[u]; p; p = E[p].next)
        {
            int v = E[p].to;
            if (!vis[v] && dis[v] > dis[u] + E[p].val) dis[v] = dis[u] + E[p].val, q.push(make_pair(dis[v], v));
        }
    }
}
int main()
{
    read(n), read(m), read(k);
    for (int i = 1, u, v, w; i <= m; ++i) read(u), read(v), read(w), add(u, v, w), add(v, u, w);
    for (int i = 1; i <= k; ++i) read(Q[i].u), read(Q[i].v), S.insert(Q[i].u), S.insert(Q[i].v);
    for (set<int>::iterator it = S.begin(); it != S.end(); ++it) dij(*it, dis[*it]);
    long long res = 1ll << 60;
    for (int j = 1; j <= 2 * m; j += 2)
    {
        long long mindis = 0;
        int cu = E[j].to,cv = E[j + 1].to;
        for (int i = 1; i <= k; ++i)
        {
            int u = Q[i].u, v = Q[i].v;
            mindis += min(dis[u][v], min(dis[u][cu] + dis[v][cv], dis[u][cv] + dis[v][cu]));
        }
        //printf("%d %d %d\n",cu, cv,mindis);
        res = min(res, mindis);
    }
    printf("%lld\n", res);
    return 0;
}