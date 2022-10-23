#include <cstdio>
#include <vector>
using namespace std;
const int maxn = 510;
int n,m,e,match[maxn],vis[maxn];
vector<int> E[maxn];
bool dfs(int u,int t)
{
    if(vis[u] == t) return 0;
    vis[u] = t;
    for(vector<int>::iterator it = E[u].begin();it!=E[u].end();++it) 
    {
        int v = *it;
        if(!match[v] || dfs(match[v],t)) return match[v] = u,1;
    }
    return 0;
}
int main()
{
    scanf("%d %d %d",&n,&m,&e);
    for (int i = 1, x, y; i <= e; ++i) scanf("%d %d", &x, &y), E[x].push_back(y);
    int ans = 0;
    for (int i = 1; i <= n; ++i) if(dfs(i,i)) ++ans;
    printf("%d\n",ans);
    return 0;
}