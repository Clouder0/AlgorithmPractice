#include <cstdio>
#include <cstring>
using namespace std;
struct node
{
    int to,next;
    node(){}
    node(const int &_to,const int &_next) : to(_to),next(_next){}
}E[3010];
int head[1510];
inline void add(const int &x,const int &y)
{
    static int tot = 0;
    E[++tot] = node(y,head[x]),head[x] = tot;
}
int n;
int fee[1510];
int dp[1510][3];
inline int min(const int &a,const int &b){return a<b?a:b;}
inline int min(const int &a,const int &b,const int &c){return min(c,min(a,b));}
//dp[i][0] self,dp[i][1] fa,dp[i][2] son
void dfs(int u,int fa)
{
    int v;
    bool flag = false;
	int minx = 999999999;
    dp[u][0] = fee[u];
    for(int p = head[u];p;p=E[p].next)
    {
        v = E[p].to;
        if(v == fa)
        	continue;
        dfs(v,u);
        dp[u][0] += min(dp[v][0],dp[v][1],dp[v][2]);
        dp[u][1] += min(dp[v][0],dp[v][2]);
        if(dp[v][0] <= dp[v][2])
        {
            dp[u][2] += dp[v][0];
            flag = true;
        }
        else
        {
            dp[u][2] += dp[v][2];
            minx = min(dp[v][0] - dp[v][2],minx);
        }
    }
    if(!flag)
        dp[u][2] += minx;
}
int main()
{
    scanf("%d",&n);
    for(int i = 1;i<=n;++i)
    {
        int x,m,t;
        scanf("%d",&x);
        scanf("%d%d",fee+x,&m);
        while(m--)
        {
            scanf("%d",&t);
            add(x,t);
            add(t,x);
        }
    }
    dfs(1,0);
    printf("%d",min(dp[1][0],dp[1][2]));
}