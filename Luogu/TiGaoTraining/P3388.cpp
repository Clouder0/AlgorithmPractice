#include <cstdio>
using namespace std;
template<typename T>
inline T min(const T &a,const T &b){return a<b?a:b;}
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxm = 1e5 + 100;
const int maxn = 2e4 + 100;
struct node
{
    int to,next;
    node(){}
    node(const int &_to,const int &_next) : to(_to),next(_next){}
}E[maxm<<1];
int head[maxn];
inline void add(const int &x,const int &y)
{
    static int tot = 0;
    E[++tot] = node(y,head[x]),head[x] = tot;
}
int n,m;
int low[maxn],dfn[maxn],time;
bool cut[maxn];
void tarjan(int u,int fa)
{
    low[u] = dfn[u] = ++time;
    int v,cs = 0;
    for(int p = head[u];p;p=E[p].next)
    {
        v = E[p].to;
        if(!dfn[v])
        {
            tarjan(v,u);
            low[u] = min(low[u],low[v]);
            if(low[v] >= dfn[u] && u != fa)
                cut[u] = 1;
            if(u == fa)
                ++cs;
        }
        low[u] = min(low[u],dfn[v]);
    }
    if(cs >= 2 && u == fa)
        cut[u] = 1;
}
int main()
{
    read(n);
    read(m);
    int a,b;
    for(int i = 1;i<=m;++i)
        read(a),read(b),add(a,b),add(b,a);
    for(int i = 1;i<=n;++i)
        if(!dfn[i])
            tarjan(i,i);
    int ans = 0;
    for(int i = 1;i<=n;++i)
        if(cut[i])
            ++ans;
    printf("%d\n",ans);
    for(int i = 1;i<=n;++i)
        if(cut[i])
            printf("%d ",i);
    return 0;
}