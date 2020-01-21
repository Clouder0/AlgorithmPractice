#include <cstdio>
using namespace std;
inline char nc()
{
    static char buf[1000000],*p1 = buf,*p2 = buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
}
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=nc();c>'9'||c<'0';c=nc());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=nc());
}
const int maxn = 1e6 + 10;
struct node
{
    int to,next;
    node(){}
    node(const int &_to,const int &_next) : to(_to),next(_next){}
}lines[maxn<<1];
int head[maxn];
inline void add(const int &x,const int &y)
{
    static int tot = 0;
    lines[++tot] = node(y,head[x]),head[x] = tot;
}
template<typename T>
inline T max(const T &a,const T &b){return a>b?a:b;}
int n;
int w[maxn];
int fa[maxn];
long long dp[maxn][2];
int root;
bool vis[maxn];
void dfs(int u)
{
    int v;
    vis[u] = true;
    dp[u][0] = 0;
    dp[u][1] = w[u];
    for(int p = head[u];p;p=lines[p].next)
    {
        v = lines[p].to;
        if(v == root)
        {
            dp[v][1] = -(1ll << 60);
            continue;
        }
        dfs(v);
        dp[u][0] += max(dp[v][0],dp[v][1]);
        dp[u][1] += dp[v][0];
    }
}
long long finalans;
inline void find()
{
    for(int i = 1;i<=n;++i)
    {
        if(!vis[i])
        {
            root = i;
            while(!vis[root])
            {
                vis[root] = 1;
                root = fa[root];
            }
            vis[root] = true;
            dfs(root);
            long long ans1 = max(dp[root][0],dp[root][1]);
            root = fa[root];
            dfs(root);
            finalans += max(ans1,max(dp[root][0],dp[root][1]));
        }
    }
}
int main()
{
    read(n);
    int temp;
    for(int i = 1;i<=n;++i)
    {
        read(w[i]);
        read(fa[i]);
        add(fa[i],i);
    }
    find();
    printf("%lld",finalans);
    return 0;
}