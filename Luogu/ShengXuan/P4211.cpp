#include <cstdio>
#include <algorithm>
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int mod = 201314;
const int maxn = 5e4 + 100;
int n,m;
namespace Graph
{
    struct node
    {
        int to,next;
    }E[maxn];
    int head[maxn],tot;
    inline void add(const int &x,const int &y){E[++tot].next = head[x],E[tot].to = y,head[x] = tot;}
}
namespace Seg
{
    #define ls (p<<1)
    #define rs (p<<1|1)
    int sum[maxn<<2],tag[maxn<<2];
    inline void pushup(const int &p){sum[p] = sum[ls] + sum[rs];sum[p] %= mod;}
    inline void pushdown(const int &l,const int &r,const int &p)
    {
        if(!tag[p]) return;
        int mid = l + r >> 1;
        sum[ls] = (sum[ls] + 1ll * (mid - l + 1) * tag[p]) % mod;
        sum[rs] = (sum[rs] + 1ll * (r - mid) * tag[p]) % mod;
        tag[ls] += tag[p],tag[rs] += tag[p];
        tag[ls] %= mod,tag[rs] %= mod;
        tag[p] = 0;
    }
    void modify(int l,int r,int p,int ll,int rr,int val)
    {
        if(ll <= l && rr >= r)
        {
            sum[p] = (sum[p] + 1ll * (r - l + 1) * val) % mod;
            tag[p] += val;
            tag[p] %= mod;
            return;
        }
        pushdown(l,r,p);
        int mid = l + r >> 1;
        if(ll <= mid) modify(l,mid,ls,ll,rr,val);
        if(rr > mid) modify(mid + 1,r,rs,ll,rr,val);
        pushup(p);
    }
    int ask(int l,int r,int p,int ll,int rr)
    {
        if(ll <= l && rr >= r) return sum[p];
        pushdown(l,r,p);
        int mid = l + r >> 1;
        int res = 0;
        if(ll <= mid) res += ask(l,mid,ls,ll,rr);
        if(rr > mid) res += ask(mid + 1,r,rs,ll,rr);
        return res % mod;
    }
}
namespace Dec
{
    int fa[maxn],size[maxn],son[maxn],dep[maxn];
    using namespace Graph;
    void dfs1(int u)
    {
        size[u] = 1, dep[u] = dep[fa[u]] + 1;
        for (int p = head[u]; p; p = E[p].next)
        {
            int v = E[p].to;
            if(v == fa[u]) continue;
            dfs1(v);
            size[u] += size[v];
            if(size[v] > size[son[u]]) son[u] = v;
        }
    }
    int top[maxn],id[maxn],time;
    void dfs2(int u)
    {
        id[u] = ++time;
        if (!son[u]) return;
        top[son[u]] = top[u], dfs2(son[u]);
        for (int p = head[u]; p; p = E[p].next)
        {
            int v = E[p].to;
            if(v == fa[u] || v == son[u]) continue;
            top[v] = v,dfs2(v);
        }
    }
    void modify(int x,int y,int k)
    {
        while(top[x] != top[y])
        {
            if(dep[top[x]] < dep[top[y]]) std::swap(x,y);
            Seg::modify(1,n,1,id[top[x]],id[x],k);
            x = fa[top[x]];
        }
        if(dep[x] > dep[y]) std::swap(x,y);
        Seg::modify(1,n,1,id[x],id[y],k);
    }
    int ask(int x,int y)
    {
        int ans = 0;
        while(top[x] != top[y])
        {
            if(dep[top[x]] < dep[top[y]]) std::swap(x,y);
            ans = (ans + Seg::ask(1,n,1,id[top[x]],id[x])) % mod;
            x = fa[top[x]];
        }
        if(dep[x] > dep[y]) std::swap(x,y);
        ans += Seg::ask(1,n,1,id[x],id[y]);
        return ans % mod;
    }
}
struct query
{
    int pos,flag,id,z;
}Q[maxn<<1];
bool cmp(const query &a,const query &b){return a.pos < b.pos;}
int ans[maxn];
int main()
{
    read(n),read(m);
    for(int i = 2;i<=n;++i) read(Dec::fa[i]),++Dec::fa[i],Graph::add(Dec::fa[i],i);
    Dec::dfs1(1),Dec::dfs2(1);
    for(int i = 1;i<=m;++i)
    {
        int l,r,z;
        read(l),read(r),read(z);
        ++l,++r,++z;
        Q[i*2-1].flag = 1,Q[i*2-1].pos = r,Q[i*2-1].id = i,Q[i*2-1].z = z;
        Q[i*2].flag = -1,Q[i*2].pos = l - 1,Q[i*2].id = i,Q[i*2].z = z;
    }
    std::sort(Q + 1,Q + 1 + m * 2,cmp);
    int p = 1;
    for(int i = 1;i<=m*2;++i)
    {
        while(p <= Q[i].pos) Dec::modify(1,p++,1);
        ans[Q[i].id] += Q[i].flag * Dec::ask(1,Q[i].z);
        ans[Q[i].id] = ((ans[Q[i].id] % mod) + mod) % mod;
    }
    for(int i = 1;i<=m;++i) printf("%d\n",ans[i]);
    return 0;
}