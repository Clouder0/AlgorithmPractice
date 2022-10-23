#include <cstdio>
const int maxn = 210;
template<typename T>
inline T min(const T &a,const T &b){return a<b?a:b;}
template<typename T>
inline int read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
    return r;
}
struct node
{
    int from,to,next;
}E[maxn * maxn];
int head[maxn];
int tot = 0;
inline void add(const int &x,const int &y)
{
    E[++tot].to = y;
    E[tot].from = x;
    E[tot].next = head[x];
    head[x] = tot;
}
int n;
int dfn[maxn],low[maxn],time;
int st[maxn],ins[maxn],stop;
int belong[maxn],num;
void tarjan(int u)
{
    dfn[u] = low[u] = ++time;
    st[++stop] = u;
    ins[u] = 1;
    int v;
    for(int p = head[u];p;p=E[p].next)
    {
        v = E[p].to;
        if(!dfn[v])
            tarjan(v),low[u] = min(low[u],low[v]);
        else if(ins[v])
            low[u] = min(low[u],dfn[v]);
    }
    if(dfn[u] == low[u])
    {
        ++num;
        int p;
        while((p = st[stop--]) != u)
            ins[p] = false,belong[p] = num;
        ins[u] = false;
        belong[u] = num;
    }
}
int in[maxn];
int main()
{
    read(n);
    int t;
    for(int i = 1;i<=n;++i)
        while(read(t))
            add(i,t);
    for(int i = 1;i<=n;++i)
        if(!dfn[i])
            tarjan(i);
    for(int i = 1;i<=tot;++i)
        if(belong[E[i].from] != belong[E[i].to])
            in[belong[E[i].to]]++;
    int ans = 0;
    for(int i = 1;i<=num;++i)
        ans += !in[i];
    printf("%d",ans);
    return 0;
}