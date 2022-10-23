#include <cstdio>
#include <vector>
#include <algorithm>
template<typename T>
inline T max(const T &a,const T &b){return a>b?a:b;}
template<typename T>
inline T min(const T &a,const T &b){return a<b?a:b;}
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 1e6 + 1000;
struct node
{
    int to,next;
}E[maxn<<1];
int head[maxn];
inline void add(const int &x,const int &y)
{
    static int tot = 0;
    E[++tot].to = y,E[tot].next = head[x],head[x] = tot;
}
int n,m,k;
int fa[maxn],dep[maxn],size[maxn],son[maxn];
void dfs1(int u)
{
    size[u] = 1;
    for(int p = head[u];p;p=E[p].next)
    {
        int v = E[p].to;
        if(v == fa[u]) continue;
        fa[v] = u,dep[v] = dep[u] + 1;
        dfs1(v);
        size[u] += size[v];
        if(size[son[u]] < size[v]) son[u] = v;
    }
}
int top[maxn],dfn[maxn],time;
void dfs2(int u,int topf)
{
    dfn[u] = ++time,top[u] = topf;
    if(!son[u]) return;
    dfs2(son[u],topf);
    for(int p = head[u];p;p=E[p].next)
    {
        int v = E[p].to;
        if(v == fa[u] || v == son[u]) continue;
        dfs2(v,v);
    }
}
inline int lca(int x,int y)
{
    while(top[x] != top[y])
    {
        if(dep[top[x]] < dep[top[y]])
        {
            int t = x;
            x = y,y = t;
        }
        x = fa[top[x]];
    }
    return dep[x] < dep[y] ? x : y;
}
std::vector<int> V[maxn];
int points[maxn],is[maxn];
int s[maxn],st;
inline void BuildTree()
{
    s[st = 1] = 1, V[1].clear();
    for (int i = 1; i <= k; ++i)
    {
        int x = points[i];
        if (x == 1) continue;
        int l = lca(x, s[st]);
        if(l == s[st]) {s[++st] = x;continue;}
        while (dfn[s[st - 1]] > dfn[l])
            V[s[st - 1]].push_back(s[st]), --st;
        if (dfn[s[st - 1]] < dfn[l])
            V[l].push_back(s[st]), s[st] = l;
        else
            V[l].push_back(s[st--]);
        s[++st] = x;
    }
    for (int i = 1; i < st; ++i)
        V[s[i]].push_back(s[i + 1]);
}
const bool cmp(const int &x, const int &y){return dfn[x] < dfn[y];}
long long ans1;
int ans2,ans3;
int size1[maxn];
int f[maxn],g[maxn];
void dp(int u)
{
    size1[u] = is[u], f[u] = 0,g[u] = is[u] ? 0 : 1<<29;
    for(std::vector<int>::iterator it = V[u].begin();it!=V[u].end();++it)
    {
        int v = *it,w = dep[v] - dep[u];
        dp(v);
        ans1 += (long long)(k - size1[v]) * size1[v] * w;
        if(size1[u] > 0)
        {
            ans2 = min(ans2,g[v] + g[u] + w);
            ans3 = max(ans3,f[v] + f[u] + w);
        }
        f[u] = max(f[u],f[v] + w);
        g[u] = min(g[u],g[v] + w);
        size1[u] += size1[v];
    }
    V[u].clear();
}
int main()
{
    read(n);
    for(int i = 1;i<n;++i)
    {
        int a,b;
        read(a),read(b);
        add(a,b),add(b,a);
    }
    dfs1(1),dfs2(1,1);
    read(m);
    while(m--)
    {
        read(k);
        for(int i = 1;i<=k;++i)
            read(points[i]),is[points[i]] = 1;
        std::sort(points + 1,points + 1 + k,cmp);
        BuildTree();
        ans1 = 0;
        ans2 = 1<<30;
        ans3 = 0;
        dp(1);
        for(int i = 1;i<=k;++i)
            is[points[i]] = 0;
        printf("%lld %d %d\n",ans1,ans2,ans3);
    }
    return 0;
}