#include <cstdio>
#include <cmath>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
inline char nc()
{
    #ifdef DEBUG
    return getchar();
    #endif
    static char buf[bufSize],*p1 = buf,*p2 = buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,bufSize,stdin),p1==p2)?EOF:*p1++;
}
template<typename T>
inline T read(T &r)
{
    static char c;
    r=0;
    for(c = nc();!isdigit(c);) c = nc();
    for(;isdigit(c);c=nc()) r = r * 10 + c - 48;
    return r;
}
const int maxn = 4e4 + 100;
const int maxm = 1e5 + 100;
namespace Graph
{
struct node
{
    int to,next;
}E[maxn<<1];
int head[maxn];
inline void add(const int &x,const int &y)
{
    static int tot = 0;
    E[++tot].next = head[x],head[x] = tot,E[tot].to = y;
}
}
int st[maxn],ed[maxn],dfn[maxn<<1],cnt;
namespace Dec
{
    int fa[maxn],size[maxn],son[maxn],dep[maxn],top[maxn];
    using namespace Graph;
    void dfs1(int u)
    {
        dfn[++cnt] = u,st[u] = ed[u] = cnt, size[u] = 1;
        for(int p = head[u];p;p=E[p].next)
        {
            int v = E[p].to;
            if (v == fa[u]) continue;
            fa[v] = u, dep[v] = dep[u] + 1, dfs1(v), size[u] += size[v];
            if (size[v] > size[son[u]]) son[u] = v;
        }
        dfn[++cnt] = u,ed[u] = cnt;
    }
    void dfs2(int u)
    {
        if(!son[u]) return;
        top[son[u]] = top[u],dfs2(son[u]);
        for(int p = head[u];p;p=E[p].next)
        {
            int v = E[p].to;
            if(v == son[u] || v == fa[u]) continue;
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
}
int n,m;
int col[maxn],H[maxn],tot;
struct ask
{
    int l,r,id,pos,lca;
}Q[maxm];
bool cmp(const ask &a,const ask &b)
{
    if(a.pos != b.pos) return a.l < b.l;
    if(a.pos & 1) return a.r < b.r;
    return a.r > b.r;
}
int ANS[maxm];
inline void init()
{
    read(n),read(m);
    for(int i = 1;i<=n;++i) read(col[i]),H[++tot] = col[i];
    std::sort(H + 1,H + 1 + tot),tot = std::unique(H + 1,H + 1 + tot) - H - 1;
    for(int i = 1;i<=n;++i) col[i] = std::lower_bound(H + 1,H + 1 + tot,col[i]) - H;
    for(int i = 1;i<n;++i)
    {
        int x,y;
        read(x),read(y),Graph::add(x,y),Graph::add(y,x);
    }
    Dec::dfs1(1), Dec::top[1] = 1, Dec::dfs2(1);
    int size = n / std::sqrt(m);
    for(int i = 1;i<=m;++i)
    {
        read(Q[i].l),read(Q[i].r),Q[i].id = i;
        Q[i].lca = Dec::lca(Q[i].l,Q[i].r);
        if(st[Q[i].l] > st[Q[i].r]) std::swap(Q[i].l,Q[i].r);
        if(Q[i].lca == Q[i].l) Q[i].l = st[Q[i].l],Q[i].r = st[Q[i].r],Q[i].lca= 0;
        else Q[i].l = ed[Q[i].l],Q[i].r = st[Q[i].r];
        Q[i].pos = Q[i].l / size;
    }
    std::sort(Q + 1,Q + 1 + m,cmp);
}
int times[maxn],used[maxn],ans;
inline void add(int x) { ans += !(times[col[x]]++); }
inline void del(int x) { ans -= !(--times[col[x]]); }
inline void modify(int x)
{
    if(used[x]) del(x); else add(x);
    used[x] ^= 1;
}
int main()
{
    init();
    int l = 1,r = 0;
    for(int i = 1;i<=m;++i)
    {
        while(l > Q[i].l) modify(dfn[--l]);
        while(r < Q[i].r) modify(dfn[++r]);
        while(l < Q[i].l) modify(dfn[l++]);
        while(r > Q[i].r) modify(dfn[r--]);
        if(Q[i].lca) modify(Q[i].lca);
        ANS[Q[i].id] = ans;
        if(Q[i].lca) modify(Q[i].lca);
    }
    for(int i = 1;i<=m;++i) printf("%d\n",ANS[i]);
    return 0;
}