#include <cstdio>
using namespace std;
const int maxn = 5e5 + 10;
int n;
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
        E[++tot].next = head[x];
        E[tot].to = y;
        head[x] = tot;
    }
}
namespace SegmentTree
{
    int sum[maxn<<2],tag[maxn<<2];
    inline void push_up(const int &p)
    {
        sum[p] = sum[p<<1] + sum[p<<1|1];
    }
    inline void push_down(const int &l,const int &r,const int &p)
    {
        if(!tag[p])
            return;
        int mid = l + r >> 1;
        tag[p<<1] = tag[p<<1|1] = tag[p];
        sum[p<<1] = (tag[p]-1) * (mid - l + 1);
        sum[p<<1|1] = (tag[p]-1) * (r - mid);
        tag[p] = 0;
    }
    void modify(const int &l,const int &r,const int &p,const int &ll,const int &rr,const int &k)
    {
        if(ll <= l && rr >= r)
        {
            sum[p] = k * (r - l + 1);
            tag[p] = k + 1;
            return;
        }
        push_down(l,r,p);
        int mid = l + r >> 1;
        if(ll <= mid)
            modify(l,mid,p<<1,ll,rr,k);
        if(rr > mid)
            modify(mid + 1,r,p<<1|1,ll,rr,k);
        push_up(p);
    }
    int ask(const int &l,const int &r,const int &p,const int &tar)
    {
        if(l == r)
            return sum[p];
        push_down(l,r,p);
        int mid = l + r >> 1;
        if(tar <= mid)
            return ask(l,mid,p<<1,tar);
        else
            return ask(mid + 1,r,p<<1|1,tar);
    }
}
namespace Decomposition
{
    int fa[maxn],id[maxn],son[maxn],size[maxn],top[maxn];
    void dfs1(int u)
    {
        size[u] = 1;
        int v;
        for(int p = Graph::head[u];p;p=Graph::E[p].next)
        {
            v = Graph::E[p].to;
            if(v == fa[u])
                continue;
            fa[v] = u;
            dfs1(v);
            size[u] += size[v];
            if(size[son[u]] < size[v])
                son[u] = v;
        }
    }
    int cnt;
    void dfs2(int u,int topfa)
    {
        id[u] = ++cnt;
        top[u] = topfa;
        if(!son[u])
            return;
        dfs2(son[u],topfa);
        int v;
        for(int p = Graph::head[u];p;p=Graph::E[p].next)
        {
            v = Graph::E[p].to;
            if(v == fa[u] || v == son[u])
                continue;
            dfs2(v,v);
        }
    }
    void fill(int x)
    {
        SegmentTree::modify(1,n,1,id[x],id[x] + size[x] - 1,1);
    }
    void empty(int x)
    {
        while(x)
        {
            SegmentTree::modify(1,n,1,id[top[x]],id[x],0);
            x = fa[top[x]];
        }
    }
    int ask(int x)
    {
        return SegmentTree::ask(1,n,1,id[x]);
    }
}
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
int q;
int main()
{
    read(n);
    int a,b;
    for(int i = 1;i<n;++i)
    {
        read(a);
        read(b);
        Graph::add(a,b);
        Graph::add(b,a);
    }
    Decomposition::dfs1(1);
    Decomposition::dfs2(1,1);
    read(q);
    while(q--)
    {
        read(a);
        read(b);
        if(a == 1)
            Decomposition::fill(b);
        else if(a == 2)
            Decomposition::empty(b);
        else
            printf("%d\n",Decomposition::ask(b));
    }
    return 0;
}