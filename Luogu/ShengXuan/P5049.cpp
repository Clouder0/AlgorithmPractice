#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn = 5e5 + 100;
vector<int> E[maxn];
int n,m,d[maxn],vis[maxn];
int backtraced;
void dfs1(int u)
{
    vis[u] = 1,printf("%d ",u);
    sort(E[u].begin(),E[u].end());
    for (vector<int>::iterator it = E[u].begin(); it != E[u].end(); ++it) if(!vis[*it]) dfs1(*it);
}
int fa[maxn],dfn[maxn],idx,inloop[maxn],cycfound;
void findloop(int u)
{
    if(cycfound) return;
    dfn[u] = ++idx;
    for(vector<int>::iterator it = E[u].begin();it!=E[u].end();++it)
    {
        int v = *it;
        if(v == fa[u]) continue;
        if(!dfn[v]) {fa[v] = u,findloop(v);continue;}
        if(dfn[v] < dfn[u]) continue;
        for (; v != u; v = fa[v]) inloop[v] = 1;
        inloop[u] = 1, cycfound = 1;
        return;
    }
}
void dfs(int u,int last)
{
    vis[u] = 1,printf("%d ",u);
    if(!inloop[u] || backtraced)
    {
        for (vector<int>::iterator it = E[u].begin(); it != E[u].end(); ++it)
            if (!vis[*it]) dfs(*it, 1 << 30);
        return;
    }
    int loopnext = 0,canbacktrace = !backtraced,mintouch = 0;
    for(vector<int>::iterator it = E[u].begin();it != E[u].end();++it)
    {
        int v = *it;
        if(vis[v]) continue;
        if(loopnext) {mintouch = v;break;}
        if (!loopnext && inloop[v]) loopnext = v;
        if (!loopnext && !inloop[v]) dfs(v, 0);
    }
    if (loopnext && !mintouch && last < loopnext) { backtraced = 1; return; }
    if(loopnext)
    {
        if (mintouch) dfs(loopnext, mintouch);
        else dfs(loopnext, last);
    }
    for (vector<int>::iterator it = E[u].begin(); it != E[u].end(); ++it)
        if (!vis[*it]) dfs(*it, 1 << 30);
}
int main()
{
    scanf("%d %d",&n,&m);
    for (int i = 1, a, b; i <= m; ++i)
        scanf("%d %d", &a, &b), E[a].push_back(b), E[b].push_back(a),d[a]++,d[b]++;
    for (int i = 1; i <= n; ++i) sort(E[i].begin(), E[i].end());
    if (m == n - 1) { dfs1(1); return 0; }
    findloop(1), dfs(1, 1 << 30);
    return 0;
}