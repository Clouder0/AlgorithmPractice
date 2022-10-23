#include <cstdio>
#include <algorithm>
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
template<typename T>
inline T max(const T &a,const T &b){return a>b?a:b;}
const int maxn = 1e5 + 100;
struct line
{
    int to,next;
}E[maxn<<1];
int head[maxn];
inline void add(const int &x,const int &y)
{
    static int tot = 0;
    E[++tot].next = head[x],head[x] = tot,E[tot].to = y;
}
int W[maxn],C[maxn];
struct node
{
    int sum,max,L,R;
}A[maxn*30];
int root[maxn],tot;
void modify(const int &l,const int &r,int &p,const int &pos,const int &k)
{
    if(!p) p = ++tot;
    if(l == r) return (void)(A[p].sum = A[p].max = k);
    int mid = l + r >> 1;
    if(pos <= mid) modify(l,mid,A[p].L,pos,k);
    else modify(mid + 1,r,A[p].R,pos,k);
    A[p].sum = A[A[p].L].sum + A[A[p].R].sum;
    A[p].max = max(A[A[p].L].max,A[A[p].R].max);
}
int asksum(const int &l,const int &r,const int &p,const int &ll,const int &rr)
{
    if(!p) return 0;
    if(l >= ll && r <= rr) return A[p].sum;
    int mid = l + r >> 1,ans = 0;
    if(ll <= mid) ans = asksum(l,mid,A[p].L,ll,rr);
    if(rr > mid) ans += asksum(mid + 1,r,A[p].R,ll,rr);
    return ans;
}
int askmax(const int &l,const int &r,const int &p,const int &ll,const int &rr)
{
    if(!p) return 0;
    if(l >= ll && r <= rr) return A[p].max;
    int mid = l + r >> 1,ans = 0;
    if(ll <= mid) ans = askmax(l,mid,A[p].L,ll,rr);
    if(rr > mid) ans = max(ans,askmax(mid + 1,r,A[p].R,ll,rr));
    return ans;
}
int n,m;
int size[maxn],fa[maxn],son[maxn],dep[maxn],top[maxn],dfn[maxn],cnt;
void dfs1(int u)
{
    size[u] = 1;
    for(int p = head[u];p;p=E[p].next)
    {
        int v = E[p].to;
        if(v == fa[u]) continue;
        fa[v] = u,dep[v] = dep[u] + 1,dfs1(v),size[u] += size[v];
        if(size[v] > size[son[u]]) son[u] = v;
    }
}
void dfs2(int u)
{
    dfn[u] = ++cnt;
    if(!son[u]) return;
    top[son[u]] = top[u],dfs2(son[u]);
    for(int p = head[u];p;p=E[p].next)
    {
        int v = E[p].to;
        if(v == fa[u] || v == son[u]) continue;
        top[v] = v,dfs2(v);
    }
}
int treesum(int x,int y)
{
    int ans = 0,p = C[x];
    while(top[x] != top[y])
    {
        if(dep[top[x]] < dep[top[y]]) std::swap(x,y);
        ans += asksum(1,n,root[p],dfn[top[x]],dfn[x]);
        x = fa[top[x]];
    }
    if(dep[x] > dep[y]) std::swap(x,y);
    ans += asksum(1,n,root[p],dfn[x],dfn[y]);
    return ans;
}
int treemax(int x,int y)
{
    int ans = 0,p = C[x];
    while(top[x] != top[y])
    {
        if(dep[top[x]] < dep[top[y]]) std::swap(x,y);
        ans = max(ans,askmax(1,n,root[p],dfn[top[x]],dfn[x]));
        x = fa[top[x]];
    }
    if(dep[x] > dep[y]) std::swap(x,y);
    ans = max(ans,askmax(1,n,root[p],dfn[x],dfn[y]));
    return ans;
}
int main()
{
    read(n),read(m);
    for(int i = 1;i<=n;++i) read(W[i]),read(C[i]);
    for(int i = 1;i<n;++i)
    {
        int x,y;
        read(x),read(y),add(x,y),add(y,x);
    }
    dfs1(1),top[1] = 1,dfs2(1);
    for(int i = 1;i<=n;++i) modify(1,n,root[C[i]],dfn[i],W[i]);
    while(m--)
    {
        char opt[5];
        int a,b;
        scanf("%s",opt + 1);
        read(a),read(b);
        if(opt[2] == 'C')
        {
            modify(1,n,root[C[a]],dfn[a],0);
            C[a] = b;
            modify(1,n,root[C[a]],dfn[a],W[a]);
        }
        else if(opt[2] == 'W') modify(1,n,root[C[a]],dfn[a],W[a] = b);
        else if(opt[2] == 'S') printf("%d\n",treesum(a,b));
        else printf("%d\n",treemax(a,b));
    }
    return 0;
}