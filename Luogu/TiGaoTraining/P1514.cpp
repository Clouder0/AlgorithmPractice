#include <cstdio>
#include <queue>
#include <algorithm>
#include <vector>
const int maxn = 510;
int n,m;
int dx[3] = {0, 0, 1};
int dy[3] = {1, -1, 0};
int h[maxn][maxn];
int vis[maxn][maxn];
struct node
{
    int l, r;
} A[maxn];
bool cmp(const node& a, const node& b)
{
    if (a.l == b.l) return a.r > b.r;
    return a.l < b.l;
}
void bfs(int u)
{
    std::queue<std::pair<int, int>> q;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) vis[i][j] = 0;
    q.push(std::make_pair(1, u));
    vis[1][u] = 1;
    while(!q.empty())
    {
        int x = q.front().first, y = q.front().second;
        q.pop();
        for(int i = 0;i<3;++i)
        {
            int nx = x + dx[i], ny = y + dy[i];
            if (vis[nx][ny] || nx > n || ny > m || ny <= 0) continue;
            if (h[x][y] > h[nx][ny]) vis[nx][ny] = 1, q.push(std::make_pair(nx, ny));
        }
    }
    for (int i = 1; i <= m; ++i)
        if (vis[n][i])
        {
            A[u].l = i;
            break;
        }
    for (int i = m; i; --i)
        if (vis[n][i])
        {
            A[u].r = i;
            break;
        }
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            scanf("%d", h[i] + j);
    for (int i = 1; i <= m; ++i) bfs(i);

    for (int i = 1; i <= m; ++i)
        for (int j = A[i].l; j <= A[i].r; ++j) vis[n][j] = 1;
    for (int i = 1; i <= m; ++i) printf("%d %d\n", A[i].l, A[i].r);
    int imp = 0;
    for (int i = 1; i <= m; ++i) if (!vis[n][i]) ++imp;
    if(imp != 0) 
    {
        printf("%d\n%d", 0, imp);
        return 0;
    }

    std::sort(A + 1, A + 1 + n, cmp);
    int ans = 0, nowl = 0, nowr = 0;
    for (int i = 1; i <= m; ++i)
    {
        if (nowl >= A[i].l) nowr = std::max(nowr, A[i].r);
        else
        {
            ++ans;
            nowl = nowr;
            nowr = std::max(nowr, A[i].r);
        }
    }
    printf("%d\n%d", ans, 0);
    return 0;
}