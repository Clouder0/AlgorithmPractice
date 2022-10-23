#include <cstdio>
#include <queue>
using namespace std;
const int maxn = 2e3 + 100, maxm = 6e3 + 100;
struct node
{
    int to, next, val;
} E[maxm];
int head[maxn], tot;
inline void add(int x, int y, int w) { E[++tot].next = head[x], head[x] = tot, E[tot].to = y, E[tot].val = w; }
int T, n, m, dis[maxn], vis[maxn], inq[maxn];
int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d %d", &n, &m);
        tot = 0;
        for (int i = 1; i <= n; ++i) head[i] = 0;
        for (int i = 1, a, b, c; i <= m; ++i)
        {
            scanf("%d %d %d", &a, &b, &c);
            if (c >= 0)
                add(a, b, c), add(b, a, c);
            else
                add(a, b, c);
        }
        queue<int> q;
        for (int i = 1; i <= n; ++i) dis[i] = 1 << 30, vis[i] = inq[i] = 0;
        dis[1] = 0, q.push(1);
        while (q.size())
        {
            int u = q.front();
            q.pop(), inq[u] = 0;
            if (vis[u] > n + 10) goto YES;
            for (int p = head[u]; p; p = E[p].next)
            {
                int v = E[p].to;
                if (dis[v] > dis[u] + E[p].val)
                {
                    dis[v] = dis[u] + E[p].val, vis[v] = vis[u] + 1;
                    if (!inq[v]) q.push(v), inq[v] = 1;
                }
            }
        }
        puts("NO");
        continue;
    YES:
        puts("YES");
        continue;
    }
    return 0;
}