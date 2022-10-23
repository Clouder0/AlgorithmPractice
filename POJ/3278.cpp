#include <cstdio>
#include <queue>
const int maxn = 2e5 + 10;
std::queue<int> q;
bool vis[maxn];
int n, k, dis[maxn];
int main()
{
    scanf("%d%d", &n, &k);
    vis[n] = 1, q.push(n);
    while (!q.empty())
    {
        int x = q.front();
        q.pop();
        if (x == k)
        {
            printf("%d", dis[x]);
            return 0;
        }
        int t = x - 1;
        if(t >= 0 && t <= 100000 && !vis[t]) vis[t] = 1, dis[t] = dis[x] + 1, q.push(t);
        t = x + 1;
        if(t >= 0 && t <= 100000 && !vis[t]) vis[t] = 1, dis[t] = dis[x] + 1, q.push(t);
        t = x * 2;
        if(t >= 0 && t <= 100000 && !vis[t]) vis[t] = 1, dis[t] = dis[x] + 1, q.push(t);
    }
    return 0;
}