#include <cstdio>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
struct node
{
    int to,next;
    node(){}
    node(const int &_to,const int &_next) : to(_to),next(_next){}
}lines[20010];
int head[10010];
inline void add(const int &x,const int &y)
{
    static int tot = 0;
    lines[++tot] = node(y,head[x]),head[x] = tot;
}
inline int min(const int &a,const int &b){return a<b?a:b;}
int n,m;
int dp[10010][2];
int c[10010];
int in[10010];
void dfs(int u,int fa)
{
    if(in[u] == 1)
    {
        dp[u][c[u]] = 1;
        dp[u][c[u]^1] = 999999999;
        return;
    }
    int v;
    dp[u][0] = dp[u][1] = 1;
    for(int p = head[u];p;p=lines[p].next)
    {
        v = lines[p].to;
        if(v == fa)
            continue;
        dfs(v,u);
        dp[u][0] += min(dp[v][0] - 1,dp[v][1]);
        dp[u][1] += min(dp[v][1] - 1,dp[v][0]);
    }
}
int main()
{
    read(n);
    read(m);
    for(int i = 1;i<=m;++i)
        read(c[i]);
    int a,b;
    for(int i = 1;i<n;++i)
    {
        read(a);
        read(b);
        ++in[a],++in[b];
        add(a,b);
        add(b,a);
    }
    int root = 0;
    for(int i = 1;!root && i<=n;++i)
        if(in[i] > 1)
            root = i;
    dfs(root,0);
    printf("%d",min(dp[root][0],dp[root][1]));
    return 0;
}