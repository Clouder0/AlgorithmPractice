#include <cstdio>
#include <cstring>

struct status
{
    int all[7][4][4];

    status()
    {
        std::memset(all, 0, sizeof(all));
    }
};

status start;
const int maxn = 1e5 + 100;
char s[maxn];

void opt(int x)
{
    status now = start;
    switch (x)
    {
        case 1:
            now.all[5][1][3] = start.all[1][1][3];
            now.all[5][2][3] = start.all[1][2][3];
            now.all[5][3][3] = start.all[1][3][3];
            now.all[6][1][3] = start.all[2][1][3];
            now.all[6][2][3] = start.all[2][2][3];
            now.all[6][3][3] = start.all[2][3][3];
            now.all[4][1][3] = start.all[4][1][1];
            now.all[4][2][3] = start.all[4][1][2];
            now.all[4][3][3] = start.all[4][1][3];
            now.all[4][1][2] = start.all[4][2][1];
            now.all[4][3][2] = start.all[4][2][3];
            now.all[4][1][1] = start.all[4][3][1];
            now.all[4][2][1] = start.all[4][3][2];
            now.all[4][3][1] = start.all[4][3][3];
            now.all[2][1][3] = start.all[5][1][3];
            now.all[2][2][3] = start.all[5][2][3];
            now.all[2][3][3] = start.all[5][3][3];
            now.all[1][1][3] = start.all[6][1][3];
            now.all[1][2][3] = start.all[6][2][3];
            now.all[1][3][3] = start.all[6][3][3];

            start = now;
            break;
        case 2:
            now.all[1][1][3] = start.all[5][1][3];
            now.all[1][2][3] = start.all[5][2][3];
            now.all[1][3][3] = start.all[5][3][3];
            now.all[2][1][3] = start.all[6][1][3];
            now.all[2][2][3] = start.all[6][2][3];
            now.all[2][3][3] = start.all[6][3][3];
            now.all[4][1][1] = start.all[4][1][3];
            now.all[4][1][2] = start.all[4][2][3];
            now.all[4][1][3] = start.all[4][3][3];
            now.all[4][2][1] = start.all[4][1][2];
            now.all[4][2][3] = start.all[4][3][2];
            now.all[4][3][1] = start.all[4][1][1];
            now.all[4][3][2] = start.all[4][2][1];
            now.all[4][3][3] = start.all[4][3][1];
            now.all[5][1][3] = start.all[2][1][3];
            now.all[5][2][3] = start.all[2][2][3];
            now.all[5][3][3] = start.all[2][3][3];
            now.all[6][1][3] = start.all[1][1][3];
            now.all[6][2][3] = start.all[1][2][3];
            now.all[6][3][3] = start.all[1][3][3];

            start = now;
            break;
        case 3:

            now.all[5][1][3] = start.all[5][1][1];
            now.all[5][2][3] = start.all[5][1][2];
            now.all[5][3][3] = start.all[5][1][3];
            now.all[5][1][2] = start.all[5][2][1];
            now.all[5][3][2] = start.all[5][2][3];
            now.all[5][1][1] = start.all[5][3][1];
            now.all[5][2][1] = start.all[5][3][2];
            now.all[5][3][1] = start.all[5][3][3];
            now.all[1][1][1] = start.all[3][1][1];
            now.all[1][1][2] = start.all[3][1][2];
            now.all[1][1][3] = start.all[3][1][3];
            now.all[2][1][1] = start.all[4][1][1];
            now.all[2][1][2] = start.all[4][1][2];
            now.all[2][1][3] = start.all[4][1][3];
            now.all[3][1][1] = start.all[2][1][1];
            now.all[3][1][2] = start.all[2][1][2];
            now.all[3][1][3] = start.all[2][1][3];
            now.all[4][1][1] = start.all[1][1][1];
            now.all[4][1][2] = start.all[1][1][2];
            now.all[4][1][3] = start.all[1][1][3];

            start = now;
            break;
        case 4:
            now.all[5][1][1] = start.all[5][1][3];
            now.all[5][1][2] = start.all[5][2][3];
            now.all[5][1][3] = start.all[5][3][3];
            now.all[5][2][1] = start.all[5][1][2];
            now.all[5][2][3] = start.all[5][3][2];
            now.all[5][3][1] = start.all[5][1][1];
            now.all[5][3][2] = start.all[5][2][1];
            now.all[5][3][3] = start.all[5][3][1];

            now.all[3][1][1] = start.all[1][1][1];
            now.all[3][1][2] = start.all[1][1][2];
            now.all[3][1][3] = start.all[1][1][3];
            now.all[4][1][1] = start.all[2][1][1];
            now.all[4][1][2] = start.all[2][1][2];
            now.all[4][1][3] = start.all[2][1][3];
            now.all[2][1][1] = start.all[3][1][1];
            now.all[2][1][2] = start.all[3][1][2];
            now.all[2][1][3] = start.all[3][1][3];
            now.all[1][1][1] = start.all[4][1][1];
            now.all[1][1][2] = start.all[4][1][2];
            now.all[1][1][3] = start.all[4][1][3];

            start = now;
            break;
        default:
            break;
    }
}

int main()
{
    scanf("%s", s + 1);
    int n = strlen(s + 1);
    char t[10];
    for (int i = 1; i <= 6; ++i)
    {
        for (int j = 1; j <= 3; ++j)
        {
            scanf("%s", t + 1);
            for (int k = 1; k <= 3; ++k)
                start.all[i][j][k] = t[k] - '0';
        }
    }
    for (int i = 1; i <= n; ++i) opt(s[i] - '0');
    for (int i = 1; i <= 6; ++i)
        for (int j = 1; j <= 3; puts(""), ++j)
            for (int k = 1; k <= 3; ++k) putchar(start.all[i][j][k] + 48);
    return 0;
}