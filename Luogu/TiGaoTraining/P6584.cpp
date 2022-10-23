#include <cstdio>
template<typename T>
inline T max(const T &a,const T &b){return a>b?a:b;}
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 4e5 + 1000;
struct node
{
    int to,next;
}E[maxn<<1];
int head[maxn];
inline void add(const int &x,const int &y)
{
    static int tot = 0;
    E[++tot].next = head[x],E[tot].to = y,head[x] = tot;
}
int n,m,root,k;
int has[maxn];
int id[maxn],dfn[maxn],cnt,size[maxn],fa[maxn][22],dep[maxn];
void dfs1(int u)
{
    dfn[u] = ++cnt;
    id[cnt] = u;
    size[u] = 1;
    for(int p = head[u];p;p=E[p].next)
    {
        int v = E[p].to;
        if(v == fa[u][0]) continue;
        dep[v] = dep[u] + 1,fa[v][0] = u;
        dfs1(v);
        size[u] += size[v];
    }
}
void initFa()
{
    for(int k = 1;(1<<k)<=n;++k)
        for(int i = 1;i<=n;++i)
            fa[i][k] = fa[fa[i][k-1]][k-1];
}
int maxp[maxn<<2],maxx[maxn<<2],tag[maxn<<2];
inline void pushup(const int &p)
{
    if(maxx[p<<1] > maxx[p<<1|1]) maxx[p] = maxx[p<<1],maxp[p] = maxp[p<<1];
    else maxx[p] = maxx[p<<1|1],maxp[p] = maxp[p<<1|1];
}
inline void pushdown(const int &p)
{
    if(!tag[p]) return;
    maxx[p<<1] += tag[p],maxx[p<<1|1] += tag[p];
    tag[p<<1] += tag[p],tag[p<<1|1] += tag[p];
    tag[p] = 0;
}
void build(const int &l,const int &r,const int &p)
{
    if(l == r)
    {
        if(has[id[l]])  maxx[p] = dep[id[l]],maxp[p] = id[l];
        return;
    }
    int mid = l + r >> 1;
    build(l,mid,p<<1),build(mid + 1,r,p<<1|1);
    pushup(p);
}
void update(const int &l,const int &r,const int &p,const int &ll,const int &rr,const int &k)
{
    if(ll <= l && rr >= r)
    {
        maxx[p] += k;
        tag[p] += k;
        return;
    }
    pushdown(p);
    int mid = l + r >> 1;
    if(ll <= mid) update(l,mid,p<<1,ll,rr,k);
    if(rr > mid) update(mid + 1,r,p<<1|1,ll,rr,k);
    pushup(p);
}
inline int getX(int u,int depth)
{
    for(int i = 21;i >= 0;--i)
        if(dep[fa[u][i]] >= depth) u = fa[u][i];
    return u;
}
int main()
{
    read(n);
    for(int i = 1;i<n;++i)
    {
        int a,b;
        read(a),read(b),add(a,b),add(b,a);
    }
    read(m);
    if(m == 0){puts("0");return 0;}
    for(int i = 1;i<=m;++i)
    {
        int x;
        read(x),has[x] = 1;
    }
    read(k),read(root);
    dfs1(root);
    build(1,n,1);
    initFa();
    int ans = 0;
    while(true)
    {
        ++ans;
        if(maxx[1] <= k)
        {
            printf("%d",ans);
            return 0;
        }
        if(maxx[1] == k + 1)
        {
            printf("%d",ans + 1);
            return 0;
        }
        int p = maxp[1];
        if(dfn[p] >= dfn[root] && dfn[p] < dfn[root] + size[root])
        {
            p = getX(p,dep[root] + 1); 
            update(1,n,1,dfn[p],dfn[p] + size[p] - 1,-2);
            root = p;
        }
        else
        {
            update(1,n,1,1,n,-2);
            update(1,n,1,dfn[root],dfn[root] + size[root] - 1,2);
            root = fa[root][0];
        }
    }
    return 0;
}