#include <cstdio>
#include <queue>
#include <memory.h>
using namespace std;
const int maxn = 5e6 + 1000;
template <typename T>
inline T _min(const T &a, const T &b)
{
    return a < b ? a : b;
}
template <typename T>
void read(T &r)
{
    static char c;r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar());
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar());
}
struct node
{
    int to, next;
} E[maxn];
int head[maxn];
int w[maxn];
int W[maxn];
int X[100100], Y[100100];
int origin[maxn];
int pos[100100][51];
int tot;
inline void add(const int &x, const int &y)
{
    E[++tot] = (node){y, head[x]}, head[x] = tot;
}
char str[100];
int n, m, d;
int low[maxn], dfn[maxn], s[maxn], st, belong[maxn], time;
bool vis[maxn],viss[100100];
void tarjan(int u)
{
    low[u] = dfn[u] = ++time;
    vis[u] = true;
    s[++st] = u;
    int v;
    for (int p = head[u]; p; p = E[p].next)
    {
        v = E[p].to;
        if (!dfn[v])
        {
            tarjan(v);
            low[u] = _min(low[u], low[v]);
        }
        else if (vis[v])
            low[u] = _min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u])
    {
        int x;
        int tt = st;
        while(x = s[tt--])
        {
            if(!viss[origin[x]] && w[x])
                ++W[u],viss[origin[x]] = true;
            if(x == u)
                break;
        }
        while (x = s[st--])
        {
            belong[x] = u;
            viss[origin[x]] = vis[x] = false;
            if (x == u)
                break;
        }
    }
}
int ans;
int dp[maxn];
int dfs(int u)
{
    if(dp[u] != -1)
        return dp[u];
    int v,maxx = 0;
    for(int p = head[u];p;p=E[p].next)
    {
        v = E[p].to;
        if(dfs(v) > maxx)
            maxx = dp[v];
    }
    return dp[u] = W[u] + maxx;
}
int main()
{
    read(n);
    read(m);
    read(d);
    for (int i = 1; i <= n; ++i)
    {
        pos[i][0] = pos[i - 1][d - 1] + 1;
        origin[pos[i][0]] = i;
        for (int j = 1; j < d; ++j)
            pos[i][j] = pos[i][j - 1] + 1,origin[pos[i][j]] = i;
    }
    for (int i = 1; i <= m; ++i)
    {
        read(X[i]);
        read(Y[i]);
        for (int j = 1; j < d; ++j)
            add(pos[X[i]][j - 1], pos[Y[i]][j]);
        add(pos[X[i]][d - 1], pos[Y[i]][0]);
    }
    for (int i = 1; i <= n; ++i)
    {
        scanf("%s", str);
        for (int j = 0; j < d; ++j)
            w[pos[i][j]] = str[j] - 48;
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j < d; ++j)
            if (!dfn[pos[i][j]])
                tarjan(pos[i][j]);
    memset(head, 0, sizeof(head));
    tot = 0;
    for (int i = 1; i <= m; ++i)
    {
        for (int j = 1; j < d; ++j)
            if (belong[pos[X[i]][j - 1]] != belong[pos[Y[i]][j]])
                add(belong[pos[X[i]][j - 1]], belong[pos[Y[i]][j]]);
        if (belong[pos[X[i]][d - 1]] != belong[pos[Y[i]][0]])
            add(belong[pos[X[i]][d - 1]], belong[pos[Y[i]][0]]);
    }
    memset(dp,-1,sizeof(dp));
    dfs(belong[pos[1][0]]);
    printf("%d", dp[belong[pos[1][0]]]);
    return 0;
}