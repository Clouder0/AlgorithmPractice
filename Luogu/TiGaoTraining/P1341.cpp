#include <cstdio>
#include <algorithm>
#include <ctype.h>
#include <vector>
using namespace std;
const int maxn = 360;
char s[maxn],st[maxn];
int n,deg[maxn], head[maxn],vis[maxn][maxn],top;
vector<int> E[maxn];
void dfs(int u)
{
    for(int &p = head[u];p < E[u].size();)
    {
        int v = E[u][p++];
        if(vis[u][v]) continue;
        vis[u][v] = vis[v][u] = 1, dfs(v);
    }
    st[++top] = u;
}
int main()
{
    scanf("%d", &n);
    int minn = 260;
    for (int i = 1; i <= n; ++i)
    {
        scanf("%s", s + 1);
        int a = s[1], b = s[2];
        E[a].push_back(b), E[b].push_back(a), deg[a]++, deg[b]++, minn = min(minn, min(a, b));
    }

    for (int i = 0; i <= 260; ++i) sort(E[i].begin(), E[i].end());
    int num = 0;
    for (int i = 0; i <= 260; ++i) num += (deg[i] & 1);
    if (num != 0 && num != 2) { puts("No Solution"); return 0; }
    for (int i = 0; i <= 260; ++i) if (deg[i] & 1) { dfs(i); goto end; }
    dfs(minn);
end:
    while (top) putchar(st[top--]);
    return 0;
}