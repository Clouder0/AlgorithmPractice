#include <cstdio>
#include <cstdlib>
using namespace std;
int n, sum;
int C[30];
void init()
{
    C[0] = C[n - 1] = 1;
    if (n > 1)
        for (int i = 1; i << 1 < n; ++i)
            C[i] = C[n - 1 - i] = (n - i) * C[i - 1] / i;
}
int path[30],vis[30],nsum;
void dfs(int now)
{
    if(nsum > sum)
        return;
    if(now == n)
    {
        if(nsum == sum)
        {
            for(int i = 1;i<=n;++i)
                printf("%d ",path[i]);
            exit(0);
        }
        return;
    }
    for(int i = 1;i<=n;++i)
        if(!vis[i])
        {
            nsum += C[now] * i;
            path[now+1] = i;
            vis[i] = 1;
            dfs(now+1);
            nsum -= C[now] * i;
            vis[i] = 0;
        }
}
int main()
{
    scanf("%d %d", &n, &sum);
    init();
    dfs(0);
    return 0;
}