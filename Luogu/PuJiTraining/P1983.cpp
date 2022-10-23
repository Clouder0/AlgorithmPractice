#include <cstdio>
#include <vector>
using namespace std;
const int maxn = 2100;
int in[maxn],n,m,tmp[maxn],vis[maxn],f[maxn],ans,q[maxn * maxn],qh,qt;
vector<int> E[maxn];
void dfs(int u)
{
    if(f[u]) return;
    for(vector<int>::iterator it = E[u].begin();it!=E[u].end();++it)
    {
        int v = *it;
        dfs(v), f[u] = max(f[u], f[v] + (u <= n));
    }
    ans = max(ans,f[u]);
}
int main()
{
    scanf("%d %d",&n,&m);
    for (int i = 1,num; i <= m; ++i)
    {
        for (int j = 1; j <= n; ++j) vis[j] = 0;
        scanf("%d",&num);
        for (int j = 1; j <= num; ++j) scanf("%d", tmp + j), vis[tmp[j]] = 1, E[n + i].push_back(tmp[j]),in[tmp[j]]++;
        for (int j = tmp[1] + 1; j < tmp[num]; ++j) if (!vis[j]) E[j].push_back(n + i),in[n + i]++;
    }
    qh = 1;
    for (int i = 1; i <= n + m; ++i) if(in[i] == 0) q[++qt] = i,f[i] = (i <= n);
    while(qt >= qh)
    {
        int u = q[qh++];
        ans = max(ans, f[u]);
        for (vector<int>::iterator it = E[u].begin(); it != E[u].end(); ++it)
        {
            int v = *it;
            f[v] = max(f[v],f[u] + (v <= n));
            if(--in[v] == 0) q[++qt] = v;
        }
    }
    printf("%d\n",ans);
    return 0;
}