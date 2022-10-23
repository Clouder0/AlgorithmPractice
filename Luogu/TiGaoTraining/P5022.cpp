#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn = 6000;
int n,m,U[maxn],V[maxn];
vector<int> E[maxn];
int cutu,cutv;
int ans[maxn],tans[maxn],cnt;
bool cmpans()
{
    for (int i = 1; i <= n; ++i) if(tans[i] != ans[i]) return tans[i] < ans[i];
    return 0;
}
bool vis[maxn];
void dfs(int u)
{
    tans[++cnt] = u,vis[u] = 1;
    for(vector<int>::iterator it = E[u].begin();it!=E[u].end();++it)
    {
        int v = *it;
        if(u == cutu && v == cutv) continue;
        if(u == cutv && v == cutu) continue;
        if(vis[v]) continue;
        dfs(v);
    }
}
int main()
{
    scanf("%d %d",&n,&m);
    for (int i = 1; i <= m; ++i) scanf("%d %d",U + i,V + i),E[U[i]].push_back(V[i]),E[V[i]].push_back(U[i]);
    for (int i = 1; i <= n; ++i) sort(E[i].begin(),E[i].end());
    if(m == n - 1)
    {
        dfs(1);
        for (int i = 1; i <= n; ++i) printf("%d ",tans[i]);
        return 0;
    }
    for (int i = 1; i <= n; ++i) ans[i] = n + 1;
    for (int i = 1; i <= m; ++i) 
    {
        cutu = U[i],cutv = V[i],cnt = 0;
        for (int j = 1; j <= n; ++j) vis[j] = 0;
        dfs(1);
        for (int j = 1; j <= n; ++j) if(!vis[j]) goto end;
        if(cmpans()) for (int j = 1; j <= n; ++j) ans[j] = tans[j];
        end:;
    }
    for (int i = 1; i <= n; ++i) printf("%d ",ans[i]);
    return 0;
}