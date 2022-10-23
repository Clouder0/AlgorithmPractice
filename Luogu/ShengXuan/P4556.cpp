#include <cstdio>
#include <algorithm>
const int maxn = 2e5 + 100;
struct node
{
    int to,next;
}E[maxn * 2];
int head[maxn];
inline void add(const int &x,const int &y)
{
    static int tot = 0;
    E[++tot].next = head[x],E[tot].to = y,head[x] = tot;
}
int n,m;
int top[maxn],fa[maxn],dep[maxn],size[maxn],son[maxn];
void dfs1(int u)
{
    size[u] = 1;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(v == fa[u]) continue;
        fa[v] = u,dep[v] = dep[u] + 1,dfs1(v),size[u] += size[v];
        if(size[v] > size[son[u]]) son[u] = v;
    }
}
void dfs2(int u)
{
    if(!son[u]) return;
    top[son[u]] = top[u],dfs2(son[u]);
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(v == fa[u] || v == son[u]) continue;
        top[v] = v,dfs2(v);
    }
}
int lca(int x,int y)
{
    while(top[x] != top[y])
    {
        if(dep[top[x]] < dep[top[y]]) std::swap(x,y);
        x = fa[top[x]];
    }
    return dep[x] < dep[y] ? x : y;
}
int maxx[maxn * 40],maxid[maxn*40],L[maxn*40],R[maxn*40],cnt,root[maxn];
inline void pushup(int p)
{
    maxx[p] = std::max(maxx[L[p]],maxx[R[p]]);
    if(maxx[p] == maxx[L[p]]) maxid[p] = maxid[L[p]];
    else maxid[p] = maxid[R[p]];
}
void modify(int l,int r,int &p,int pos,int k)
{
    if(!p) p = ++cnt;
    if (l == r) return (void)(maxid[p] = l, maxx[p] += k);
    int mid = l + r >> 1;
    if(pos <= mid) modify(l,mid,L[p],pos,k);
    else modify(mid +1,r,R[p],pos,k);
    pushup(p);
}
int merge(int l,int r,int x,int y)
{
    if(!x || !y) return x + y;
    if(l == r) 
    {
        maxid[x] = l,maxx[x] += maxx[y];
        return x;
    }
    int mid = l + r >> 1;
    L[x] = merge(l, mid, L[x], L[y]), R[x] = merge(mid + 1, r, R[x], R[y]), pushup(x);
    return x;
}
const int maxz = 1e5 + 100;
int ans[maxn];
void dfs3(int u)
{
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(v == fa[u]) continue;
        dfs3(v),root[u] = merge(1,maxz,root[u],root[v]);
    }
    ans[u] = maxx[root[u]] ? maxid[root[u]] : 0;
}
int main()
{
    scanf("%d %d",&n,&m);
    for (int i = 1,a,b; i < n; ++i) scanf("%d %d",&a,&b),add(a,b),add(b,a);
    dfs1(1),top[1] = 1,dfs2(1);
    while(m--)
    {
        int a,b,c;
        scanf("%d %d %d",&a,&b,&c);
        modify(1,maxz,root[a],c,1);
        modify(1,maxz,root[b],c,1);
        int l = lca(a,b);
        modify(1,maxz,root[fa[l]],c,-1);
        modify(1,maxz,root[l],c,-1);
    }
    dfs3(1);
    for (int i = 1; i <= n; ++i) printf("%d\n",ans[i]);
    return 0;
}