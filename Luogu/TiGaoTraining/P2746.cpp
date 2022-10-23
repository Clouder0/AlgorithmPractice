#include <cstdio>
using namespace std;
template<typename T>
inline T _min(const T &a,const T &b){return a<b?a:b;}
template<typename T>
inline T read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
    return r;
}
const int maxn = 110;
struct node
{
    int from,to,next;
}E[maxn * maxn];
int head[maxn];
int tot;
inline void add(const int &x,const int &y)
{
    E[++tot].to = y;
    E[tot].from = x;
    E[tot].next = head[x];
    head[x] = tot;
}
int n;
int dfn[maxn],low[maxn],time;
int s[maxn],ins[maxn],top;
int num,belong[maxn];
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
            dfs(v),low[u] = _min(low[u],low[v]);
        else if(ins[v])
            low[u] = _min(low[u],dfn[v]);
    }
    if(low[u] == dfn[u])
    {
        ++num;
        int p;
        while((p = s[top--]) != u)
            ins[p] = false,belong[p] = num;
        ins[u] = false;
        belong[u] = num;
    }
}
int in[maxn],out[maxn];
int main()
{
    read(n);
    int t;
    for(int i = 1;i<=n;++i)
        while(read(t))
            add(i,t);
    for(int i = 1;i<=n;++i)
        if(!dfn[i])
            dfs(i);
    for(int i = 1;i<=tot;++i)
        if(belong[E[i].from] != belong[E[i].to])
            in[belong[E[i].to]]++,out[belong[E[i].from]]++;
    int ina = 0,outa = 0;
    if(num == 1)
    {
        printf("1\n0");
        return 0;
    }
    for(int i = 1;i<=num;++i)
        ina += !in[i],outa += !out[i];
    printf("%d\n",ina>1?ina:1);
    printf("%d",ina>outa?ina:outa);
    return 0;
}