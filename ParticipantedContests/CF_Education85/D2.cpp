#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 50;
int n;
int vis[maxn][maxn];
int path[maxn];
int temp[maxn];
int maxt;
void dfs(int u,int t)
{
    temp[t] = u;
    maxt = t>maxt?t:maxt;
    bool over = true;
    for(int i = 1;i<=n;++i)
        for(int j = 1;j<=n;++j)
            if(i != j && !vis[i][j])
                over = false;
    if(over)
    {
        for(int i = 1;i<=maxt;++i)
            if(temp[i] < path[i])
            {
                for(int j = 1;j<=maxt;++j)
                    path[j] = temp[j];
                break;
            }
            else if(temp[i] > path[i])
                break;
        return;
    }
    for(int i = 1;i<=n;++i)
        if(i != u && !vis[u][i])
        {
            vis[u][i] = 1;
            dfs(i,t+1);
            vis[u][i] = 0;
        }
}
int main()
{
    memset(path,0x3f,sizeof(path));
    scanf("%d",&n);
    dfs(1,1);
    for(int i = 1;i<=maxt;++i)
        printf("%d ",path[i]);
    return 0;
}