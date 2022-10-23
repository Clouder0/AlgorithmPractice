#include <cstdio>
const int maxn = 3e5 + 10;
template<typename T>
inline void _swap(T &a,T &b)
{
    T t = a;
    a = b;
    b = t;
}
int n,m;
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
        E[++tot].to = y;
        E[tot].next = head[x];
        head[x] = tot;
    }
}
namespace Decomposition
{
    int wt[maxn];
}
namespace SegmentTree
{
    int sum[maxn<<2];
    inline void push_up(const int &p)
    {
        sum[p] = sum[p<<1] + sum[p<<1|1];
    }
    void modify(const int &l,const int &r,const int &p,const int &tar,const int &k)
    {
        if(l == r)
        {
            sum[p] = k;
            return;
        }
        int mid = l + r >> 1;
        if(tar <= mid)
            modify(l,mid,p<<1,tar,k);
        else
            modify(mid + 1,r,p<<1|1,tar,k);
        push_up(p);
    }
    int ask(const int &l,const int &r,const int &p,const int &ll,const int &rr)
    {
        if(ll <= l && rr >= r)
            return sum[p];
        int mid = l + r >> 1;
        int res = 0;
        if(ll <= mid)
            res += ask(l,mid,p<<1,ll,rr);
        if(rr > mid)
            res += ask(mid + 1,r,p<<1|1,ll,rr);
        return res;
    }
}
namespace Decomposition
{
    int top[maxn],fa[maxn],size[maxn],son[maxn],dep[maxn],cnt;
    void dfs(int u)
    {
        dep[u] = dep[fa[u]] + 1;
        size[u] = 1;
        int v;
        for(int p = Graph::head[u];p;p=Graph::E[p].next)
        {
            v = Graph::E[p].to;
            if(v == fa[u])
                continue;
            fa[v] = u;
            dfs(v);
            size[u] += size[v];
            if(size[son[u]] < size[v])
                son[u] = v;
        }
    }
    int id[maxn];
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
    int askSum(int x,int y)
    {
        int res = 0;
        while(top[x] != top[y])
        {
            if(dep[top[x]] < dep[top[y]])
                _swap(x,y);
            res += SegmentTree::ask(1,n,1,id[top[x]],id[x]);
            x = fa[top[x]];
        }
        if(x == y)
            return res;
        if(dep[x] > dep[y])
            _swap(x,y);
        return res + SegmentTree::ask(1,n,1,id[x] + 1,id[y]);
    }
}
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
int war[maxn],tot;
int main()
{
    read(n);
    read(m);
    int x,y;
    for(int i = 1;i<n;++i)
    {
        read(x);
        read(y);
        Graph::add(x,y);
        Graph::add(y,x);
    }
    Decomposition::dfs(1);
    Decomposition::dfs2(1,1);
    char s[10];
    while(m--)
    {
        scanf("%s",s + 1);
        read(x);
        if(s[1] == 'Q')
        {
            read(y);
            if(Decomposition::askSum(x,y))
                puts("No");
            else
                puts("Yes");
        }
        else if(s[1] == 'C')
        {
            read(y);
            if(Decomposition::fa[x] == y)
                SegmentTree::modify(1,n,1,Decomposition::id[x],1),war[++tot] = Decomposition::id[x];
            else
                SegmentTree::modify(1,n,1,Decomposition::id[y],1),war[++tot] = Decomposition::id[y];
        }
        else
        {
            SegmentTree::modify(1,n,1,war[x],0);
        }
    }
    return 0;
}