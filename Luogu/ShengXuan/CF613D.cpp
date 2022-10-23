#include <cstdio>
#include <vector>
#include <algorithm>
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 1e5 + 100;
int n,q;
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
namespace Dec
{
    int fa[maxn],size[maxn],son[maxn],dep[maxn];
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
        top[u] = topf,dfn[u] = ++time;
        if(!son[u]) return;
        dfs2(son[u],topf);
        for(int p = head[u];p;p=E[p].next)
        {
            int v = E[p].to;
            if(v == fa[u] || v == son[u])  continue;
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
}
int points[maxn],is[maxn];
int s[maxn],top;
std::vector<int> V[maxn];
inline void addV(const int &x,const int &y){if(x == y) return;V[x].push_back(y);}
inline void push(int x)
{
    if(x == 1)  return;
    int l = Dec::lca(x, s[top]);
    while (Dec::dfn[s[top - 1]] > Dec::dfn[l])
        addV(s[top - 1], s[top]), --top;
    if (Dec::dfn[s[top - 1]] < Dec::dfn[l])
        V[l].clear(), addV(l, s[top]), s[top] = l;
    else
        addV(l,s[top--]);
    V[x].clear(),s[++top] = x;
}
int f[maxn],g[maxn];
void dp(int u)
{
    f[u] = g[u] = 0;
    for(std::vector<int>::iterator it = V[u].begin();it!=V[u].end();++it)
    {
        dp(*it);
        f[u] += f[*it],g[u] += g[*it];
    }
    if(is[u]) f[u] += g[u],g[u] = 1;
    else if(g[u] > 1) g[u] = 0,++f[u];
}
const bool cmp(const int &x,const int &y){return Dec::dfn[x] < Dec::dfn[y];}
int main()
{
    read(n);
    for(int i = 1;i<n;++i)
    {
        int x,y;
        read(x),read(y);
        add(x,y),add(y,x);
    }
    Dec::dfs1(1),Dec::dfs2(1,1);
    read(q);
    while(q--)
    {
        int k;
        read(k);
        for(int i = 1;i<=k;++i)
            read(points[i]),is[points[i]] = 1;
        for(int i = 1;i<=k;++i)
            if(is[Dec::fa[points[i]]])
            {
                puts("-1");
                goto end;
            }
        std::sort(points + 1,points + 1 + k,cmp);
        s[top = 1] = 1,V[1].clear();
        for(int i = 1;i<=k;++i)
            push(points[i]);
        for(int i = 1;i<top;++i)
            addV(s[i],s[i+1]);
        dp(1);
        printf("%d\n",f[1]);
        end:
        for(int i = 1;i<=k;++i)
            is[points[i]] = 0;
    }
    return 0;
}