#include <cstdio>
#include <algorithm>
#include <cmath>
#include <ctype.h>
#define DEBUG
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
const int maxn = 1e5 + 100;
int n,m,q;
int V[maxn],W[maxn],C[maxn];
namespace Graph
{
    struct node
    {
        int to,next;
    }E[maxn<<1];
    int head[maxn],tot;
    inline void add(const int &x,const int &y){E[++tot].next = head[x],head[x] = tot,E[tot].to = y;}
}
int dfn[maxn<<1],cnt,st[maxn],ed[maxn];
namespace Dec
{
    int size[maxn],dep[maxn],fa[maxn],son[maxn],top[maxn];
    using namespace Graph;
    void dfs1(int u)
    {
        size[u] = 1,dfn[++cnt] = u,st[u] = cnt;
        for(int p = head[u];p;p = E[p].next)
        {
            int v = E[p].to;
            if(v == fa[u]) continue;
            fa[v] = u,dep[v] = dep[u] + 1,dfs1(v),size[u] += size[v];
            if(size[v] > size[son[u]]) son[u] = v;
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
            if(v == fa[u] || v == son[u]) continue;
            top[v] = v,dfs2(v);
        }
    }
    inline int lca(int x,int y)
    {
        while(top[x] != top[y])
        {
            if(dep[top[x]] < dep[top[y]]) std::swap(x,y);
            x = fa[top[x]];
        }
        return dep[x] < dep[y] ? x : y;
    }
}
struct ask
{
    int l,r,lpos,rpos,t,id,lca;
}Q[maxn];
struct modify
{
    int pos,target;
}M[maxn];
bool cmp(const ask &a,const ask &b)
{
    if (a.lpos != b.lpos) return a.l < b.l;
    if (a.rpos != b.rpos) return a.r < b.r;
    return a.t < b.t;
}
int qnum,mnum;
inline void init();
int times[maxn],used[maxn];
long long ans;
inline void add(int x)
{
    ans += 1ll * W[++times[C[x]]] * V[C[x]];
}
inline void del(int x) 
{
    ans -= 1ll * W[times[C[x]]--] * V[C[x]];
}
inline void work(int x)
{
    used[x]? del(x) : add(x);
    used[x] ^= 1;
}
inline void change(int cid)
{
    int pos = M[cid].pos,&val = M[cid].target;
    if(used[pos])
    {
        ans -= 1ll * W[times[C[pos]]--] * V[C[pos]];
        ans += 1ll * W[++times[val]] * V[val];
    } 
    std::swap(val,C[pos]);
}
long long ANS[maxn];
int main()
{
    init();
    int l = 1,r = 0,t = 0;
    for(int i = 1;i<=qnum;++i)
    {
        while(l > Q[i].l) work(dfn[--l]);
        while(r < Q[i].r) work(dfn[++r]);
        while(l < Q[i].l) work(dfn[l++]);
        while(r > Q[i].r) work(dfn[r--]);
        while(t < Q[i].t) change(++t);
        while(t > Q[i].t) change(t--);
        if(Q[i].lca) work(Q[i].lca);
        ANS[Q[i].id] = ans;
        if(Q[i].lca) work(Q[i].lca);
    }
    for(int i = 1;i<=qnum;++i) printf("%lld\n",ANS[i]);
    return 0;
}
inline void init()
{
    read(n),read(m),read(q);
    for(int i = 1;i<=m;++i) read(V[i]);
    for(int i = 1;i<=n;++i) read(W[i]);
    for(int i = 1;i<n;++i)
    {
        int x,y;
        read(x),read(y),Graph::add(x,y),Graph::add(y,x);
    }
    int size = std::pow(n,0.66666);
    Dec::dfs1(1),Dec::top[1] = 1,Dec::dfs2(1);
    for(int i = 1;i<=n;++i) read(C[i]);
    for(int i = 1;i<=q;++i)
    {
        int type,x,y;
        read(type),read(x),read(y);
        if (type == 0) M[++mnum].pos = x, M[mnum].target = y;
        else
        {
            Q[++qnum].id = qnum,Q[qnum].t = mnum;
            Q[qnum].lca = Dec::lca(x,y);
            if(st[x] > st[y]) std::swap(x,y);
            if(Q[qnum].lca == x) Q[qnum].l = st[x],Q[qnum].r = st[y],Q[qnum].lca = 0;
            else Q[qnum].l = ed[x],Q[qnum].r = st[y];
            Q[qnum].lpos = Q[qnum].l / size,Q[qnum].rpos = Q[qnum].r / size;
        }
    }
    std::sort(Q + 1,Q + 1 + qnum,cmp);
}