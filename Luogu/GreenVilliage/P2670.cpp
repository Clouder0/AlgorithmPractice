#include <cstdio>

const int maxn = 1e3 + 100;
int n, m;
char s[maxn][maxn];
int dx[8] = {
    1,
    1,
    1,
    -1,
    -1,
    -1,
    0,
    0,
};
int dy[8] = {
    1,
    0,
    -1,
    1,
    0,
    -1,
    1,
    -1,
};
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%s", s[i] + 1);
    for (int i = 1; i <= n; puts(""), ++i)
        for (int j = 1; j <= m; ++j)
        {
            if (s[i][j] == '*')
            {
                putchar('*');
                continue;
            }
            int ttt = 0;
            for (int k = 0; k < 8; ++k)
            {
                int nx = i + dx[k], ny = j + dy[k];
                if (nx <= 0 || nx > n || ny <= 0 || ny > m) continue;
                ttt += (s[nx][ny] == '*');
            }
            putchar(48 + ttt);
        }
    return 0;
}