#include <cstdio>
#include <queue>
const int maxn = 1e3;
char s[maxn][maxn];
int T, n, m, gx0, gy0, gx1, gy1, sx0, sy0, sx1, sy1;
int vis[2][maxn][maxn];
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};
int abs(const int& x) { return x >= 0 ? x : -x; }
bool touch(int x, int y, int t)
{
    if(abs(gx0 - x) + abs(gy0 - y) <= t * 2) return true;
    if(abs(gx1 - x) + abs(gy1 - y) <= t * 2) return true;
    return false;
}
bool check(int x,int y)
{
//    printf("check %d %d %d %d\n",x,y,vis[0][x][y], vis[1][x][y]);
    return vis[0][x][y] && vis[1][x][y];
}
struct node
{
    int x,y,t,left_step;
};
struct node2
{
    int x,y,t;
};
int main()
{
    scanf("%d", &T);
    while(T--)
    {
        sx0 = sy0 = sx1 = sy1 = gx0 = gy0 = gx1 = gy1 = 0;
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; ++i) scanf("%s",s[i] + 1);
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j) 
            {
                vis[0][i][j] = vis[1][i][j] = 0;
                if(s[i][j] == 'Z') 
                {
                    if (!gx0)
                        gx0 = i, gy0 = j;
                    else
                        gx1 = i, gy1 = j;
                }
                else if (s[i][j] == 'M') sx0 = i, sy0 = j;
                else if (s[i][j] == 'G') sx1 = i, sy1 = j;
            }
        std::queue<node> q0;
        std::queue<node2> q1;
        q0.push({sx0, sy0, 1, 3});
        q1.push({sx1, sy1, 1});
        vis[0][sx0][sy0] = vis[1][sx1][sy1] = 1;
        int curT = 1;
        while (!q0.empty() && !q1.empty())
        {
            while (!q0.empty() && q0.front().t == curT)
            {
                node now = q0.front();
                q0.pop();
                if (touch(now.x, now.y, now.t)) continue;
                for (int i = 0; i < 4; ++i)
                {
                    int nx = now.x + dx[i], ny = now.y + dy[i];
                    if (nx <= 0 || nx > n || ny <= 0 || ny > m) continue;
                    if (touch(nx, ny, now.t)) continue;
                    if (vis[0][nx][ny]) continue;
                    if (s[nx][ny] == 'X') continue;
                    vis[0][nx][ny] = now.t;
                    node nn = {nx, ny, now.t, now.left_step - 1};
                    if (nn.left_step == 0) ++nn.t, nn.left_step = 3;
                    q0.push(nn);
                    if(check(nx,ny)) 
                    {
                        printf("%d\n",now.t);
                        goto end;
                    }
                }
            }
            while(!q1.empty() && q1.front().t == curT)
            {
                node2 now = q1.front();
                q1.pop();
                if(touch(now.x,now.y,now.t)) continue;
                for (int i = 0; i < 4; ++i)
                {
                    int nx = now.x + dx[i], ny = now.y + dy[i];
                    if (nx <= 0 || nx > n || ny <= 0 || ny > m) continue;
                    if (touch(nx, ny, now.t)) continue;
                    if (vis[1][nx][ny]) continue;
                    if (s[nx][ny] == 'X') continue;
                    vis[1][nx][ny] = now.t;
                    q1.push({nx, ny, now.t + 1});
                    if(check(nx,ny))
                    {
                        printf("%d\n",now.t);
                        goto end;
                    }
                }
            }
            ++curT;
        }
        puts("-1");
    end:
    ;
    }
    return 0;
}