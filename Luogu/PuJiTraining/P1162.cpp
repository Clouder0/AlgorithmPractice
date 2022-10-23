#include <cstdio>
#include <cstdlib>
#include <queue>
using namespace std;
int all[50][50];
int n;
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};
void bfs()
{
    queue<pair<int, int>> q;
    q.push(make_pair(0, 0));
    all[0][0] = 3;
    int x, y, nx, ny;
    while (!q.empty())
    {
        x = q.front().first;
        y = q.front().second;
        q.pop();
        for (int i = 0; i < 4; ++i)
        {
            nx = x + dx[i];
            ny = y + dy[i];
            if (nx >= 0 && nx <= n + 1 && ny >= 0 && ny <= n + 1 && all[nx][ny] == 0)
            {
                q.push(make_pair(nx, ny));
                all[nx][ny] = 3;
            }
        }
    }
    for (int i = 1; i <= n; putchar('\n'), ++i)
        for (int j = 1; j <= n; ++j)
            if (all[i][j] == 0)
                printf("2 ");
            else if (all[i][j] == 1)
                printf("1 ");
            else
                printf("0 ");
    exit(0);
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            scanf("%d", &all[i][j]);
    //从0,0开始扫
    bfs();
    return 0;
}