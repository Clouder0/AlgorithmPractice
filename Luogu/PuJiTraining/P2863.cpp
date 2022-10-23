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
const int maxn = 2e4 + 100;
const int maxm = 5e4 + 100;
struct node
{
    int to,next;
}E[maxm];
int head[maxn];
inline void add(const int &x,const int &y)
{
    static int tot = 0;
    E[++tot].to = y;
    E[tot].next = head[x];
    head[x] = tot;
}
int n,m;
int dfn[maxn],low[maxn],time;
int ins[maxn],s[maxn],st;
int cnt,num[maxn],belong[maxn];
void dfs(int u)
{
    dfn[u] = low[u] = ++time;
    ins[u] = 1,s[++st] = u;
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
        belong[u] = ++cnt;
        num[cnt] = 1;
        ins[u] = 0;
        int t;
        while((t=s[st--]) != u)
        {
            belong[t] = cnt;
            ++num[cnt];
            ins[t] = 0;
        }
    }
}
int main()
{
    read(n);
    read(m);
    for(int i = 1;i<=m;++i)
    {
        int a,b;
        read(a);
        read(b);
        add(a,b);
    }
    for(int i = 1;i<=n;++i)
        if(!dfn[i])
            dfs(i);
    int ans = 0;
    for(int i = 1;i<=cnt;++i)
        if(num[i] > 1)
            ++ans;
    printf("%d",ans);
    return 0;
}