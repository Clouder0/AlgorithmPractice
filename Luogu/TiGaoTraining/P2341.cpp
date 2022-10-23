#include <cstdio>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
template<typename T>
inline T min(const T &a,const T &b){return a<b?a:b;}
const int maxn = 1e4 + 100;
struct node
{
    int to,next;
    node(){}
    node(const int &_to,const int &_next) : to(_to),next(_next){}
}E[5*maxn];
int head[maxn];
inline void add(const int &x,const int &y)
{
    static int tot = 0;
    E[++tot] = node(y,head[x]),head[x] = tot;
}
int n,m;
int low[maxn],dfn[maxn],time,s[maxn],st,ins[maxn];
int belong[maxn];
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
            low[u] = min(low[u],low[v]);
        }
        else if(ins[v])
            low[u] = min(low[u],dfn[v]);
    }
    if(low[u] == dfn[u])
    {
        int x;
        while(x = s[st--])
        {
            ins[x] = false;
            belong[x] = u;
            if(x == u)
                break;
        }
    }
}
int X[5*maxn],Y[5*maxn];
int out[maxn];
int main()
{
    read(n);
    read(m);
    int x,y;
    for(int i = 1;i<=m;++i)
    {
        read(X[i]);
        read(Y[i]);
        add(X[i],Y[i]);
    }
    for(int i = 1;i<=n;++i)
        if(!dfn[i])
            tarjan(i);
    for(int i = 1;i<=m;++i)
        if(belong[X[i]] != belong[Y[i]])
            out[belong[X[i]]]++;
    int ansbelong = 0;
    int ans = 0;
    for(int i = 1;i<=n;++i)
        if(out[belong[i]] == 0)
        {
            if(ansbelong == 0 || ansbelong == belong[i])
                ++ans,ansbelong = belong[i];
            else
            {
                puts("0");
                return 0;
            }
        }
    printf("%d",ans);
    return 0;
}