#include <cstdio>
using namespace std;
template<typename T>
inline T min(const T &a,const T &b){return a<b?a:b;}
template<typename T>
inline T max(const T &a,const T &b){return a>b?a:b;}
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 8e4 + 10;
const int maxm = 2e5 + 10;
struct node
{
    int from,to,next,val;
    double ret;
    node(){}
    node(const int &_from,const int &_to,const int &_next,const int &_val,const double &_ret) : from(_from),to(_to),next(_next),val(_val),ret(_ret){}
}E[maxm],E2[maxm];
int head[maxn],head2[maxn];
inline void add(const int &x,const int &y,const int &val,const double &ret)
{
    static int tot = 0;
    E[++tot] = node(x,y,head[x],val,ret),head[x] = tot;
}
inline void add2(const int &x,const int &y,const int &val)
{
    static int tot = 0;
    E2[++tot] = node(x,y,head2[x],val,0),head2[x] = tot;
}
int n,m,s;
int dfn[maxn],low[maxn],idx;
int st[maxn],ins[maxn],top;
int belong[maxn],num[maxn],sn;
int V[maxn];
void dfs(int u)
{
    dfn[u] = low[u] = ++idx;
    st[++top] = u;
    ins[u] = true;
    int v;
    for(int p = head[u];p;p=E[p].next)
    {
        v = E[p].to;
        if(!dfn[v])
            dfs(v),low[u] = min(low[u],low[v]);
        else if(ins[v])
            low[u] = min(low[u],dfn[v]);
    }
    if(low[u] == dfn[u])
    {
        ++sn;
        int p;
        while ((p = st[top--]) != u)
        {
            belong[p] = sn;
            ins[p] = false;
        }
        belong[u] = sn;
        ins[u] = false;
    }
}
int in[maxn];
int q[maxn],qh,qt;
int f[maxn];
void topo()
{
    for(int i = 1;i<=sn;++i)
    {
        f[i] = -(1<<30);
        if(!in[i])
            q[++qt] = i;
    }
    qh = 1;
    f[belong[s]] = V[belong[s]];
    int u,v;
    while(qt >= qh)
    {
        u = q[qh++];
        for(int p = head2[u];p;p=E2[p].next)
        {
            v = E2[p].to;
            f[v] = max(f[v],f[u] + E2[p].val + V[v]);
            if(--in[v] == 0)
                q[++qt] = v;
        }
    }
    int ans = -(1<<30);
    for(int i = 1;i<=sn;++i)
        ans = max(ans,f[i]);
    printf("%d",ans);
}
int main()
{
    scanf("%d %d",&n,&m);
    int x,y,z;
    double ret;
    for(int i = 1;i<=m;++i)
    {
        scanf("%d %d %d %lf",&x,&y,&z,&ret);
        add(x,y,z,ret);
    }
    for(int i = 1;i<=n;++i)
        if(!dfn[i])
            dfs(i);
    for(int i = 1;i<=m;++i)
    {
        if(belong[E[i].from] == belong[E[i].to])
        {
            int t = E[i].val;
            while(t)
            {
                V[belong[E[i].from]] += t;
                t *= E[i].ret;
            }
        }
        else
            add2(belong[E[i].from],belong[E[i].to],E[i].val),in[belong[E[i].to]]++;
    }
    read(s);
    topo();
    return 0;
}