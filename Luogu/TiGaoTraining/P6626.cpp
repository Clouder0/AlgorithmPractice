#include <cstdio>
#include <vector>
#include <cstring>
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
int T;
const int maxn = 1e5 + 100;
struct node
{
    int to,next;
}E[maxn];
int head[maxn],tot;
inline void add(const int &x,const int &y){E[++tot].next = head[x],E[tot].to = y,head[x] = tot;}
int n,m;
int vis[maxn],size[maxn],maxp[maxn];
int root,treeSize;
void getroot(int u,int from)
{
    size[u] = 1,maxp[u] = 0;
    for(int p = head[u];p;p=E[p].next)
    {
        int v = E[p].to;
        if(vis[v] || v == from) continue;
        getroot(v,u);
        size[u] += size[v];
        if(size[v] > maxp[u]) maxp[u] = size[v];
    }
    if(treeSize - size[u] > maxp[u]) maxp[u] = treeSize - size[u];
    if(maxp[u] < maxp[root]) root = u;
}
std::vector<std::pair<int,int> > Q[maxn];
int ans[maxn],dis[maxn],s[maxn*2],stop;
void getdis(int u,int from)
{
    s[++stop] = u;
    for(int p = head[u];p;p=E[p].next)
    {
        int v = E[p].to;
        if(vis[v] || v == from) continue;
        dis[v] = dis[u] + 1;
        getdis(v,u);
    }
}
int rem[maxn];
void calc(int u)
{
    stop = 0;
    dis[u] = 0,s[++stop] = u;
    for(int p = head[u];p;p=E[p].next)
    {
        int v = E[p].to;
        if(vis[v]) continue;
        dis[v] = 1,getdis(v,0);
    }
    for(int i = 1;i<=stop;++i) rem[dis[s[i]]]++;
    for(std::vector<std::pair<int,int> >::iterator it = Q[u].begin();it!=Q[u].end();++it)
    {
        int k = it->first,id = it->second;
        ans[id] += rem[k];
    }
    for(int p = head[u];p;p=E[p].next)
    {
        int v = E[p].to;
        if(vis[v]) continue;
        int t = stop;
        dis[v] = 1,getdis(v,0);
        for(int i = t + 1;i<=stop;++i) rem[dis[s[i]]]--;
        for(int i = t + 1;i<=stop;++i) 
        {
            for(std::vector<std::pair<int,int> >::iterator it = Q[s[i]].begin();it!=Q[s[i]].end();++it)
            {
                int k = it->first,id = it->second;
                if(k >= dis[s[i]]) ans[id] += rem[k - dis[s[i]]];
            }
        }
        for(int i = t + 1;i<=stop;++i) rem[dis[s[i]]]++;
        stop = t;
    }
    for(int i = 1;i<=stop;++i) rem[dis[s[i]]] = 0;
}
void solve(int u)
{
    maxp[root = 0] = 1<<30,getroot(u,0);
//    if(size[root] == 1) return;
    vis[root] = 1;
    calc(root);
    for(int p = head[root];p;p=E[p].next)
    {
        int v = E[p].to;
        if(vis[v]) continue;
        treeSize = size[v],solve(v);
    }
}
int query[maxn];
int main()
{
    read(T);
    while(T--)
    {
        read(n),read(m);
        for(int i = 1;i<n;++i)
        {
            int a,b;
            read(a),read(b);
            add(a,b),add(b,a);
        }
        for(int i = 1;i<=m;++i)
        {
            int x,k;
            read(x),read(k);
            Q[x].push_back(std::make_pair(k,i));
        }
        treeSize = n,solve(1);
        for(int i = 1;i<=m;++i)  printf("%d\n",ans[i]);
        for(int i = 1;i<=m;++i) ans[i] = 0,Q[i].clear();
        for(int i = 1;i<=n;++i) vis[i] = 0,head[i] = 0;
        tot = 0;
    }
    return 0;
}