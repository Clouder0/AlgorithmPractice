#include <cstdio>
using namespace std;
char all[101][101];
bool vis[101][101];
int dx[8] = {0, 0, 1, -1, 1, 1, -1, -1};
int dy[8] = {1, -1, 0, 0, 1, -1, 1, -1};
char word[8] = {'y', 'i', 'z', 'h', 'o', 'n', 'g'};
int direction, n;
int path[8];
void dfs(int nx, int ny, int k)
{
    if (k == 8)
    {
        //走到头了
        for (int i = 1; i < 8; ++i)
        {
            nx = path[i] >> 16;
            ny = (path[i] << 16) >> 16;
            vis[nx][ny] = true;
        }
        return;
    }
    path[k] = (nx << 16) + ny;
    nx += dx[direction];
    ny += dy[direction];
    if (all[nx][ny] == word[k] || k == 7)
        dfs(nx, ny, k + 1);
}
int main()
{
    scanf("%d", &n);
    int i,j;
    for (i = 1; i <= n; ++i)
        scanf("%s", all[i] + 1);
    for (i = 1; i <= n; ++i)
        for (j = 1; j <= n; ++j)
            if (all[i][j] == 'y')
                for (direction = 0; direction < 8; ++direction)
                    dfs(i, j, 1);
    for (i = 1; i <= n; putchar('\n'), ++i)
        for (j = 1; j <= n; ++j)
            putchar((vis[i][j] ? all[i][j] : '*'));
    return 0;
}