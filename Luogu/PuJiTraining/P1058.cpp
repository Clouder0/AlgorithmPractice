#include <cstdio>

const int maxn = 2e3 + 100;

char s[maxn][maxn];
int n, m, a[maxn][maxn];
int maxx,maxy;

void stretch(int x, int y)
{
    if (x + 6 > maxx) maxx = x + 6;
    if (y + 5 > maxy) maxy = y + 5;
}

void draw(int x, int y)
{
    // printf("draw %d %d\n", x, y);
    s[x][y] = '+';
    s[x + 1][y] = '-';
    s[x + 2][y] = '-';
    s[x + 3][y] = '-';
    s[x + 4][y] = '+';
    s[x][y + 1] = '|';
    s[x][y + 2] = '|';
    s[x][y + 3] = '+';
    s[x + 4][y + 1] = '|';
    s[x + 4][y + 2] = '|';
    s[x + 4][y + 3] = '+';
    s[x + 1][y + 3] = '-';
    s[x + 2][y + 3] = '-';
    s[x + 3][y + 3] = '-';
    s[x + 1][y + 4] = '/';
    s[x + 5][y + 4] = '/';
    s[x + 2][y + 5] = '+';
    s[x + 3][y + 5] = '-';
    s[x + 4][y + 5] = '-';
    s[x + 5][y + 5] = '-';
    s[x + 6][y + 5] = '+';
    s[x + 6][y + 4] = '|';
    s[x + 6][y + 3] = '|';
    s[x + 6][y + 2] = '+';
    s[x + 5][y + 1] = '/';
    s[x + 1][y + 1] = s[x + 2][y + 1] = s[x + 3][y + 1] = ' ';
    s[x + 1][y + 2] = s[x + 2][y + 2] = s[x + 3][y + 2] = ' ';
    s[x+2][y+4] = s[x + 3][y + 4] = s[x + 4][y + 4] =  ' ';
    s[x + 5][y + 2] = s[x + 5][y + 3] = ' ';
}

void output()
{
    for (int i = maxy; i >= 0; puts(""), --i)
        for (int j = 0; j <= maxx; ++j) putchar(s[j][i]);
}

void threeDdraw(int x, int y, int z)
{
    int calcx = 4 * (x - 1) + 2 * (y - 1);
    int calcy = 2 * (y - 1) + 3 * (z - 1);
    draw(calcx, calcy);
}

void threeDstretch(int x, int y, int z)
{
    int calcx = 4 * (x - 1) + 2 * (y - 1);
    int calcy = 2 * (y - 1) + 3 * (z - 1);
    stretch(calcx, calcy);
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) scanf("%d", a[i] + j);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            for (int k = 1; k <= a[i][j]; ++k)
                threeDstretch(j, n - i + 1, k);
    for (int i = 0; i <= maxx; ++i)
        for (int j = 0; j <= maxy; ++j) s[i][j] = '.';
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            for (int k = 1; k <= a[i][j]; ++k)
                threeDdraw(j, n - i + 1, k);
    output();
    return 0;
}