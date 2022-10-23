#include <cstdio>
template<typename T>
inline T min(const T &a,const T &b){return a<b?a:b;}
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 1e5 + 100;
const int maxm = 5e5 + 100;
struct node
{
    int from,to,next;
}E[maxm];
int head[maxn],tot;
inline void add(const int &x,const int &y)
{
    E[++tot].to = y;
    E[tot].from = x;
    E[tot].next = head[x];
    head[x] = tot;
}
int n,m;
int dfn[maxn],low[maxn],time;
int s[maxn],ins[maxn],top;
int belong[maxn],num;
void dfs(int u)
{
    dfn[u] = low[u] = ++time;
    s[++top] = u;
    ins[u] = 1;
    int v;
    for(int p = head[u];p;p=E[p].next)
    {
        v = E[p].to;
        if(!dfn[v])
            dfs(v),low[u] = min(low[u],low[v]);
        else if(ins[v])
            low[u] = min(low[u],dfn[v]);
    }
    if(dfn[u] == low[u])
    {
        int p;
        ++num;
        while((p = s[top--]) != u)
            ins[p] = false,belong[p] = num;
        ins[u] = false;
        belong[u] = num;
    }
}
int in[maxn];
int main()
{
    read(n);
    read(m);
    int a,b;
    for(int i = 1;i<=m;++i)
    {
        read(a);
        read(b);
        add(a,b);
    }
    for(int i = 1;i<=n;++i)
        if(!dfn[i])
            dfs(i) ;
    for(int i = 1;i<=m;++i)
        if(belong[E[i].from] != belong[E[i].to])
            in[belong[E[i].to]]++;
    int ans = 0;
    for(int i = 1;i<=num;++i)
        ans += !in[i];
    printf("%d",ans);
    return 0;
}