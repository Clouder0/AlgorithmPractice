#include <algorithm>
#include <cstdio>
const int maxn = 1e3 + 100;
int n, m;
char s[maxn][maxn];
int vis[maxn][maxn];
int qt, qh = 1;
std::pair<int, int> q[maxn * maxn];
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%s", s[i] + 1);
    int res = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (s[i][j] == 'o') q[++qt] = std::make_pair(i, j), vis[i][j] = 1;
    while (qt >= qh)
    {
        int x = q[qh].first, y = q[qh].second;
        ++qh;
        if (x > 1 && !vis[x - 1][y] && s[x - 1][y] == 'd') q[++qt] = std::make_pair(x - 1, y), vis[x - 1][y] = 1;
        if (x < n && !vis[x + 1][y] && s[x + 1][y] == 'u') q[++qt] = std::make_pair(x + 1, y), vis[x + 1][y] = 1;
        if (y > 1 && !vis[x][y - 1] && s[x][y - 1] == 'r') q[++qt] = std::make_pair(x, y - 1), vis[x][y - 1] = 1;
        if (y < m && !vis[x][y + 1] && s[x][y + 1] == 'l') q[++qt] = std::make_pair(x, y + 1), vis[x][y + 1] = 1;
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) res += vis[i][j];
    printf("%d\n", res);
    return 0;
}