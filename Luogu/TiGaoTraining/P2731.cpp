#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;
const int maxn = 11000;
int n,vis[maxn][maxn],deg[maxn],head[maxn],ans[maxn],top;
vector<int> V[maxn];
void dfs(int u)
{
    for (int& p = head[u]; p < V[u].size();)
    {
        int v = V[u][p++];
        if (vis[u][v] == 0) continue;
        vis[u][v]--,vis[v][u]--, dfs(v);
    }
    ans[++top] = u;
}
int main()
{
    scanf("%d",&n);
    int s = 600;
    for (int i = 1,a,b; i <= n; ++i) 
    {
        scanf("%d %d", &a, &b);
        V[a].push_back(b), V[b].push_back(a);
        deg[a]++, deg[b]++;
        s = min(s, min(a, b));
        vis[a][b]++, vis[b][a]++;
    }
    for (int i = 1; i <= n; ++i) sort(V[i].begin(),V[i].end());
    for (int i = 1; i <= n; ++i) if (deg[i] & 1) { dfs(i); goto end; }
    dfs(s);
    end:
    while(top) printf("%d\n",ans[top--]);
    return 0;
}