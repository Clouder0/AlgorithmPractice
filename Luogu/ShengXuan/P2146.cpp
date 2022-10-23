#include <cstdio>
using namespace std;
template<typename T>
inline void swap(T &a,T &b)
{
    T t = a;
    a = b;
    b = t;
}
template<typename T>
inline T read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
    return r;
}
const int maxn = 1e5 + 1000;
int n,m;
namespace Graph
{
    struct node
    {
        int to,next;
    }E[maxn];
    int head[maxn];
    int tot;
    inline void add(const int &x,const int &y)
    {
        E[++tot] = (node){y,head[x]},head[x] = tot;
    }
}
namespace SegmentTree
{
    int sum[maxn<<2],tag[maxn<<2];
    inline void push_up(const int &p)
    {
        sum[p] = sum[p<<1] + sum[p<<1|1];
    }
    inline void push_down(int l,int r,const int &p)
    {
        if(tag[p] == -1)
            return;
        tag[p<<1] = tag[p<<1|1] = tag[p];
        int mid = l+r>>1;
        sum[p<<1] = tag[p] * (mid-l+1);
        sum[p<<1|1] = tag[p] * (r - mid);
        tag[p] = -1;
    }
    void build(const int &l,const int &r,const int &p)
    {
        tag[p] = -1;
        if(l == r)
            return;
        int mid = l+r>>1;
        build(l,mid,p<<1);
        build(mid+1,r,p<<1|1);
        push_up(p);
    }
    int ll,rr,k;
    void modify(const int &l,const int &r,const int &p)
    {
        if(ll <= l && rr >= r)
        {
            tag[p] = k;
            sum[p] = k * (r-l+1);
            return;
        }
        push_down(l,r,p);
        int mid = l+r>>1;
        if(ll <= mid)
            modify(l,mid,p<<1);
        if(rr > mid)
            modify(mid+1,r,p<<1|1);
        push_up(p);
    }
}
namespace HeavyDecomposition
{
    int fa[maxn],son[maxn],dep[maxn],size[maxn];
    using namespace Graph;
    void dfs1(int u,int deep)
    {
        dep[u] = deep;
        size[u] = 1;
        int v,maxx = -1;
        for(int p = head[u];p;p=E[p].next)
        {
            v = E[p].to;
            dfs1(v,deep+1);
            size[u] += size[v];
            if(size[v] > maxx)
                son[u] = v,maxx = size[v];
        }
    }
    int id[maxn],top[maxn],cnt;
    void dfs2(int u,int topf)
    {
        id[u] = ++cnt;
        top[u] = topf;
        if(!son[u])
            return;
        dfs2(son[u],topf);
        int v;
        for(int p = head[u];p;p=E[p].next)
        {
            v = E[p].to;
            if(v == son[u])
                continue;
            dfs2(v,v);
        }
    }
    using namespace SegmentTree;
    int changeRange(int x,int y,int val)
    {
        int res = sum[1];
        while(top[x] != top[y])
        {
            if(dep[top[x]] < dep[top[y]])
                swap(x,y);
            ll = id[top[x]];
            rr = id[x];
            k = val;
            modify(1,n,1);
            x = fa[top[x]];
        }
        if(dep[x] > dep[y])
            swap(x,y);
        ll = id[x];
        rr = id[y];
        k = val;
        modify(1,n,1);
        res -= sum[1];
        if(res < 0)
            res = -res;
        return res;
    }
    int changeSon(int x,int val)
    {
        int res = sum[1];
        ll = id[x];
        rr = id[x] + size[x] - 1;
        k = val;
        modify(1,n,1);
        res -= sum[1];
        if(res < 0)
            res = -res;
        return res;
    }
}
int main()
{
    read(n);
    for(int i = 2;i<=n;++i)
        read(HeavyDecomposition::fa[i]),Graph::add(++HeavyDecomposition::fa[i],i);
    HeavyDecomposition::dfs1(1,1);
    HeavyDecomposition::dfs2(1,1);
    SegmentTree::build(1,n,1);
    read(m);
    char opt[100];
    int target;
    while(m--)
    {
        scanf("%s",opt);
        read(target);
        ++target;
        if(opt[0] == 'i')
            printf("%d\n",HeavyDecomposition::changeRange(1,target,1));
        else
            printf("%d\n",HeavyDecomposition::changeSon(target,0));
    }
    return 0;
}