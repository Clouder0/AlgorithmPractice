#include <cstdio>
#include <queue>
#include <vector>
using namespace std;
const int maxn = 1e4 + 10;
const int maxm = 4e5 + 10;
struct node
{
    int to, next, val;
} E[maxm];
int head[maxn], cnt;
inline void add(int u, int v, int w)
{
    E[++cnt].next = head[u], head[u] = cnt, E[cnt].to = v, E[cnt].val = w;
}
int n, m, vis[maxn], dis[maxn];
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1, a, b, c; i <= m; ++i) scanf("%d%d%d", &a, &b, &c), add(a, b, c), add(b, a, c);
    for (int i = 1; i <= n; ++i) dis[i] = 1 << 30;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    q.push({0, 1});
    dis[1] = 0;
    int sum = 0, cnt = 0;
    while (!q.empty())
    {
        int u = q.top().second;
        q.pop();
        if (vis[u]) continue;
        vis[u] = 1, ++cnt;
        sum += dis[u];
        for (int p = head[u]; p; p = E[p].next)
        {
            int v = E[p].to;
            if (!vis[v] && dis[v] > E[p].val)
                dis[v] = E[p].val, q.push({dis[v], v});
        }
    }
    if (cnt == n) printf("%d\n", sum);
    else puts("orz");
    return 0;
}
