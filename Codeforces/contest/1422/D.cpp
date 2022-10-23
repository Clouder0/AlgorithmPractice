#include <algorithm>
#include <cstdio>
#include <ctype.h>
#include <vector>
#include <queue>
#include <map>
const int bufSize = 1e6;
#define int long long
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
const int maxn = 1e6;
int n, m, sx, sy, tx, ty;
struct point
{
    int x, y;
} P[maxn];
map<int,vector<int> > X,Y;
struct node
{
    int to,next,val;
}E[maxn];
int head[maxn];
inline void add(const int &x,const int &y,const int &val)
{
    static int tot = 0;
    E[++tot].next = head[x], E[tot].to = y, E[tot].val = val, head[x] = tot;
}
inline int dis(int x1, int y1, int x2, int y2) { return min(std::abs(x1 - x2) , std::abs(y1 - y2)); }
inline int dis2(int x1, int y1, int x2, int y2) { return std::abs(x1 - x2) + std::abs(y1 - y2); }
long long dist[maxn];
bool vis[maxn];
void dij()
{
    priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > q;
    for (int i = 0; i <= n + 1; ++i) (dist[i] = 1ll << 60);
    dist[0] = 0, q.push(make_pair(dist[0], 0));
    while (!q.empty())
    {
        int u = q.top().second;
        q.pop();
        if(vis[u]) continue;
        vis[u] = 1;
        if(u == n + 1) return;
        for (int p = head[u],v; p; p = E[p].next)
            if (!vis[v = E[p].to] && dist[v] > dist[u] + E[p].val)
            {
                dist[v] = dist[u] + E[p].val;
                q.push(make_pair(dist[v], v));
            }
    }
}
signed main()
{
    read(m), read(n);
    read(sx), read(sy), read(tx), read(ty);
    for (int i = 1, x, y; i <= n; ++i) read(x), read(y), X[x].push_back(i), Y[y].push_back(i), P[i].x = x, P[i].y = y;
    for (int i = 1; i <= n; ++i) add(0, i, dis(sx, sy, P[i].x, P[i].y)), add(i, n + 1, dis2(tx, ty, P[i].x, P[i].y));
    add(0, n + 1, dis2(sx, sy, tx, ty));
    for (map<int, vector<int> >::iterator V = X.begin(); V != X.end(); ++V)
    {
        map<int, vector<int> >::iterator T = V;
        ++T;
        if (T != X.end()) add(V->second[0], T->second[0], T->first - V->first),add(T->second[0],V->second[0],T->first - V->first);
        for(int i = 1;i < V->second.size();++i) add(V->second[i - 1], V->second[i], 0),add(V->second[i],V->second[i-1],0);
    }
    for (map<int, vector<int> >::iterator V = Y.begin(); V != Y.end(); ++V)
    {
        map<int, vector<int> >::iterator T = V;
        ++T;
        if (T != Y.end()) add(V->second[0], T->second[0], T->first - V->first),add(T->second[0],V->second[0],T->first - V->first);
        for(int i = 1;i < V->second.size();++i) add(V->second[i - 1], V->second[i], 0),add(V->second[i],V->second[i-1],0);
    }
    dij();
    printf("%lld\n",dist[n + 1]);
    return 0;
}