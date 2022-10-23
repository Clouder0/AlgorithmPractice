#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;
int n, m, sx, sy;
int all[1510][1510];
bool vis[1510][1510];
int firstx[1510][1510],firsty[1510][1510];
char temp[1510];
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};
struct node
{
    int x, y, px, py;
    node() {}
    node(const int &_x, const int &_y, const int &_px, const int &_py) : x(_x), y(_y), px(_px), py(_py) {}
};
int main()
{
    while (cin >> n >> m)
    {
        queue<node> q;
        memset(all, 0, sizeof(all));
        memset(vis, 0, sizeof(vis));
        memset(firstx,0,sizeof(firstx));
        memset(firsty,0,sizeof(firsty));
        for (int i = 0; i < n; ++i)
        {
            scanf("%s", temp);
            for (int j = 0; j < m; ++j)
                if (temp[j] == '#')
                    all[i][j] = 1;
                else if (temp[j] == 'S')
                    sx = i, sy = j;
        }
        q.push(node(sx, sy,sx,sy));
        node now;
        while (!q.empty())
        {
            now = q.front();
            q.pop();
            if (vis[now.px][now.py] && (firstx[now.px][now.py] != now.x || firsty[now.px][now.py] != now.y))
            {
                printf("Yes\n");
                goto end;
            }
            if(vis[now.px][now.py])
                continue;
            vis[now.px][now.py] = true;
            firstx[now.px][now.py] = now.x;
            firsty[now.px][now.py] = now.y;
            for (int i = 0; i < 4; ++i)
            {
                int nx = (dx[i] + now.px + n) % n;
                int ny = (dy[i] + now.py + m) % m;
                if (all[nx][ny] == 1)
                    continue;
                q.push(node(now.x + dx[i],now.y + dy[i],nx, ny));
            }
        }
        printf("No\n");
    end:;
    }
    return 0;
}