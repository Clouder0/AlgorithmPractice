#include <cstdio>
#include <queue>
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
inline T _min(const T &a,const T &b){return a<b?a:b;}
const int maxn = 1e5 + 10;
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
int n,m;
int time,low[maxn],dfn[maxn],ins[maxn],s[maxn],st;
int belong[maxn],W[maxn];
void tarjan(int u)
{
    low[u] = dfn[u] = ++time;
    s[++st] = u;
    ins[u] = 1;
    int v;
    for(int p = head[u];p;p=E[p].next)
    {
        v = E[p].to;
        if(!dfn[v])
        {
            tarjan(v);
            low[u] = _min(low[v],low[u]);
        }
        else if(ins[v])
            low[u] = _min(low[u],dfn[v]);
    }
    if(low[u] == dfn[u])
    {
        int x;
        while(x = s[st--])
        {
            belong[x] = u;
            W[u]++;
            ins[x] = 0;
            if(x == u)
                break;
        }
    }
}
int X[maxn],Y[maxn];
int dis[2][maxn];
queue<int> q;
inline void spfa(int *dis,int s)
{
    dis[s] = W[s];
    q.push(s);
    int u,v;
    while(!q.empty())
    {
        u = q.front();
        q.pop();
        for(int p = head[u];p;p=E[p].next)
        {
            v = E[p].to;
            if(dis[v] < dis[u] + W[v])
            {
                dis[v] = dis[u] + W[v];
                q.push(v);
            }
        }
    }
}
int main()
{
    read(n);
    read(m);
    for(int i = 1;i<=m;++i)
    {
        read(X[i]);
        read(Y[i]);
        add(X[i],Y[i]);
    }
    for(int i = 1;i<=n;++i)
        if(!dfn[i])
            tarjan(i);
    tot = 0;
    memset(head,0,sizeof(head));
    for(int i = 1;i<=m;++i)
        if(belong[X[i]] != belong[Y[i]])
            add(belong[X[i]],belong[Y[i]]);
    spfa(dis[0],belong[1]);
    tot = 0;
    memset(head,0,sizeof(head));
    for(int i = 1;i<=m;++i)
        if(belong[X[i]] != belong[Y[i]])
            add(belong[Y[i]],belong[X[i]]);
    spfa(dis[1],belong[1]);
    int ans = W[belong[1]];
    for(int i = 1;i<=m;++i)
        if(belong[X[i]] != belong[Y[i]] && dis[0][belong[Y[i]]] > 0 && dis[1][belong[X[i]]] > 0 && dis[0][belong[Y[i]]] + dis[1][belong[X[i]]] - W[belong[1]] > ans)
            ans = dis[0][belong[Y[i]]] + dis[1][belong[X[i]]] - W[belong[1]];
    printf("%d",ans);
    return 0;
}