#include <cstdio>
#include <memory.h>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
template<typename T>
inline void swap(T &a,T &b)
{
    T t = a;
    a = b;
    b = t;
}
const int maxn = 1e5 + 1000;
int n,m;
namespace Graph
{
    int to[maxn<<1],next[maxn<<1];
    int head[maxn],tot;
    int w[maxn];
    inline void add(const int &x,const int &y)
    {
        ++tot;
        next[tot] = head[x];
        to[tot] = y;
        head[x] = tot;
    }
}
namespace Decomposition
{
    int wt[maxn];
}
namespace Seg
{
    int num[maxn<<2],lc[maxn<<2],rc[maxn<<2],tag[maxn<<2];
    inline void push_up(const int &p)
    {
        num[p] = num[p<<1] + num[p<<1|1];
        if(rc[p<<1] == lc[p<<1|1])
            --num[p];
        lc[p] = lc[p<<1];
        rc[p] = rc[p<<1|1];
    }
    inline void  push_down(const int &p)
    {
        if(tag[p] == -1)
            return;
        num[p<<1] = num[p<<1|1] = 1;
        lc[p<<1] = rc[p<<1] = tag[p];
        lc[p<<1|1] = rc[p<<1|1] = tag[p];
        tag[p<<1] = tag[p<<1|1] = tag[p];
        tag[p] = -1;
    }
    void build(const int &l,const int &r,const int &p)
    {
        tag[p] = -1;
        if(l == r)
        {
            lc[p] = rc[p] = Decomposition::wt[l];
            num[p] = 1;
            return;
        }
        int mid = l + r >> 1;
        build(l,mid,p<<1);
        build(mid+1,r,p<<1|1);
        push_up(p);
    }
    void modify(const int &l,const int &r,const int &p,const int &k,const int &ll,const int &rr)
    {
        if(ll <= l && rr >= r)
        {
            tag[p] = k;
            num[p] = 1;
            lc[p] = rc[p] = k;
            return;
        }
        push_down(p);
        int mid = l + r >> 1;
        if(ll <= mid)
            modify(l,mid,p<<1,k,ll,rr);
        if(rr > mid)
            modify(mid+1,r,p<<1|1,k,ll,rr);
        push_up(p);
    }
    struct res
    {
        int lc,rc,num;
    };
    res ask(const int &l,const int &r,const int &p,const int &ll,const int &rr)
    {
        if(ll <= l && rr >= r)
            return (res){lc[p],rc[p],num[p]};
        push_down(p);
        int mid = l + r >> 1;
        if(ll > mid)
            return ask(mid+1,r,p<<1|1,ll,rr);
        if(rr <= mid)
            return ask(l,mid,p<<1,ll,rr);
        res left = ask(l,mid,p<<1,ll,rr),right = ask(mid+1,r,p<<1|1,ll,rr);
        res ans;
        ans.lc = left.lc;
        ans.rc = right.rc;
        ans.num = left.num + right.num;
        if(left.rc == right.lc)
            --ans.num;
        return ans;
    }
}
namespace Decomposition
{
    using namespace Graph;
    int fa[maxn],size[maxn],son[maxn],dep[maxn];
    int vis[maxn],st[maxn],stop;
    inline void dfs1()
    {
        stop = 0;
        st[++stop] = 1;
        int u,v;
        while(stop)
        {
            u = st[stop];
            if(vis[u] == 2)
                continue;
            if(vis[u] == 1)
            {
                for(int p = head[u];p;p=next[p])
                {
                    v = to[p];
                    if(v == fa[u])
                        continue;
                    size[u] += size[v];
                    if(size[son[u]] < size[v])
                        son[u] = v;
                }
                --stop;
                vis[u] = 2;
                continue;
            }
            vis[u] = 1;
            size[u] = 1;
            for(int p = head[u];p;p=next[p])
            {
                v = to[p];
                if(v == fa[u])
                    continue;
                fa[v] = u;
                dep[v] = dep[u] + 1;
                st[++stop] = v;
            }
        }
    }
    int id[maxn],top[maxn],cnt;
    inline void dfs2()
    {
        stop = 0;
        st[++stop] = 1;
        top[1] = 1;
        memset(vis,0,sizeof(vis));
        int u,v;
        while(stop)
        {
            u = st[stop];
            if(vis[u])
            {
                --stop;
                continue;
            }
            vis[u] = 1;
            id[u] = ++cnt;
            wt[cnt] = w[u];
            if(!son[u])
                continue;
            for(int p = head[u];p;p=next[p])
            {
                v = to[p];
                if(v == son[u] || v == fa[u])
                    continue;
                st[++stop] = v;
                top[v] = v;
            }
            st[++stop] = son[u];
            top[son[u]] = top[u];
        }
    }
    inline void change(int x,int y,int c)
    {
        while(top[x] != top[y])
        {
            if(dep[top[x]] < dep[top[y]])
                swap(x,y);
            Seg::modify(1,n,1,c,id[top[x]],id[x]);
            x = fa[top[x]];
        }
        if(dep[x] > dep[y])
            swap(x,y);
        Seg::modify(1,n,1,c,id[x],id[y]);
    }
    inline int ask(int x,int y)
    {
        int ans = 0;
        int c1 = -1,c2 = -1;
        Seg::res t;
        while(top[x] != top[y])
        {
            if(dep[top[x]] < dep[top[y]])
                swap(x,y),swap(c1,c2);
            t = Seg::ask(1,n,1,id[top[x]],id[x]);
            ans += t.num;
            if(t.rc == c1)
                --ans;
            c1 = t.lc;
            x = fa[top[x]];
        }
        if(dep[x] > dep[y])
            swap(x,y),swap(c1,c2);
        t = Seg::ask(1,n,1,id[x],id[y]);
        ans += t.num;
        if(t.lc == c1)
            --ans;
        if(t.rc == c2)
            --ans;
        return ans;
    }
}
int main()
{
    read(n);
    read(m);
    for(int i = 1;i<=n;++i)
        read(Graph::w[i]);
    int a,b;
    for(int i = 1;i<n;++i)
        read(a),read(b),Graph::add(a,b),Graph::add(b,a);
    Decomposition::dfs1();
    Decomposition::dfs2();
    Seg::build(1,n,1);
    char s[10];
    int c;
    while(m--)
    {
        scanf("%s",s);
        read(a);
        read(b);
        if(s[0] ==  'Q')
            printf("%d\n",Decomposition::ask(a,b));
        else
        {
            read(c);
            Decomposition::change(a,b,c);
        }
    }
    return 0;
}