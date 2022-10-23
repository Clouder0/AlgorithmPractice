#include <cstdio>
template<typename T>
void read(T &r)
{
    static char c;static int flag = 1;r=0;flag = 1;
    for(c=getchar();c>'9'||c<'0';c=getchar())
        if(c == '-') flag = -1;
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());r*=flag;
}
struct node
{
    int to,next;
    node(){}
    node(const int &_to,const int &_next) : to(_to),next(_next){}
}lines[40000];
int head[17000];
inline void add(const int &x,const int &y)
{
    static int tot = 0;
    lines[++tot] = node(y,head[x]),head[x] = tot;
}
int n;
int w[17000];
int dp[17000];
void dfs(int u,int fa)
{
    dp[u] = w[u];
    int v;
    for(int p = head[u];p;p=lines[p].next)
    {
        v = lines[p].to;
        if(v == fa)
            continue;
        dfs(v,u);
        dp[u] += dp[v];
    }
    if(dp[u] < 0)
        dp[u] = 0;
}
int main()
{
    read(n);
    for(int i = 1;i<=n;++i)
        read(w[i]);
    int x,y;
    for(int i = 1;i<n;++i)
    {
        read(x);
        read(y);
        add(x,y);
        add(y,x);
    }
    dfs(1,0);
    int ans = dp[1];
    for(int i = 2;i<=n;++i)
        if(dp[i] > ans)
            ans = dp[i];
    printf("%d",ans);
    return 0;
}