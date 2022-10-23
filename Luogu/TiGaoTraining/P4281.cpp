#include <cstdio>
#include <algorithm>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 5e5 + 10;
struct node
{
    int to,next;
}E[maxn<<1];
int head[maxn];
inline void add(const int &x,const int &y)
{
    static int tot = 0;
    E[++tot].to = y;
    E[tot].next = head[x];
    head[x] = tot;
}
int dep[maxn],top[maxn],id[maxn],fa[maxn],size[maxn],son[maxn],cnt;
void dfs1(int u)
{
    dep[u] = dep[fa[u]] + 1;
    size[u] = 1;
    int v;
    for(int p = head[u];p;p=E[p].next)
    {
        v = E[p].to;
        if(v == fa[u])
            continue;
        fa[v] = u;
        dfs1(v);
        size[u] += size[v];
        if(size[v] > size[son[u]])
            son[u] = v;
    }
}
void dfs2(int u,int topfa)
{
    id[u] = ++cnt;
    top[u] = topfa;
    if(!son[u])
        return;
    dfs2(son[u],topfa);
    int v;
    for(int p = head[u];p;p=E[p].next)
    {
        v = E[p].to;
        if(v == son[u] || v== fa[u])
            continue;
        dfs2(v,v);
    }
}
inline int lca(int x,int y)
{
    while(top[x] != top[y])
    {
        if(dep[top[x]] < dep[top[y]])
            swap(x,y);
        x = fa[top[x]];
    }
    if(dep[x] > dep[y])
        swap(x,y);
    return x;
}
int n,m;
int main()
{
    read(n);
    read(m);
    int x,y;
    for(int i = 1;i<n;++i)
    {
        read(x);
        read(y);
        add(x,y);
        add(y,x);
    }
    dfs1(1);
    dfs2(1,1);
    int a,b,c;
    while(m--)
    {
        read(a);
        read(b);
        read(c);
        int p = lca(a,b);
        int q = lca(a,c);
        int k = lca(b,c);
        if(p == q)
            printf("%d %d\n",k,dep[a] + dep[b] + dep[c] - dep[k] - dep[p] * 2);
        else if(p == k)
            printf("%d %d\n",q,dep[a] + dep[b] + dep[c] - dep[q] - dep[p] * 2);
        else
            printf("%d %d\n",p,dep[a] + dep[b] + dep[c] - dep[p] - dep[q] * 2);
    }
    return 0;
}