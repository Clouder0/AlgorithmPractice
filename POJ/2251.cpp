#include <cstdio>
#include <queue>
const int maxn = 50;
int n, m, q;
char s[maxn][maxn][maxn];
bool vis[maxn][maxn][maxn];
int dx[] = {1, -1, 0, 0, 0, 0};
int dy[] = {0, 0, 1, -1, 0, 0};
int dz[] = {0, 0, 0, 0, 1, -1};
struct node
{
    int x, y, z, step;
};
int main()
{
    while (scanf("%d%d%d", &n, &m, &q) != EOF)
    {
        if (n == 0 && m == 0 && q == 0) return 0;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j) scanf("%s", s[i][j] + 1);
        int sa, sb, sc;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                for (int k = 1; k <= q; ++k)
                    if (s[i][j][k] == 'S')
                    {
                        sa = i, sb = j, sc = k;
                        goto out;
                    }
    out:
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                for (int k = 1; k <= q; ++k) vis[i][j][k] = 0;
        std::queue<node> Q;
        vis[sa][sb][sc] = 1;
        Q.push((node){sa, sb, sc, 0});
        while (!Q.empty())
        {
            int x = Q.front().x, y = Q.front().y, z = Q.front().z, step = Q.front().step;
            Q.pop();
            if (s[x][y][z] == 'E')
            {
                printf("Escaped in %d minute(s).\n", step);
                goto end;
            }
            for (int i = 0; i < 6; ++i)
            {
                int nx = x + dx[i], ny = y + dy[i], nz = z + dz[i];
                if (nx <= 0 || nx > n || ny <= 0 || ny > m || nz <= 0 || nz > q) continue;
                if (vis[nx][ny][nz]) continue;
                if (s[nx][ny][nz] == '#') continue;
                Q.push((node){nx, ny, nz, step + 1}), vis[nx][ny][nz] = 1;
            }
        }
        puts("Trapped!");
    end:;
    }
    return 0;
}