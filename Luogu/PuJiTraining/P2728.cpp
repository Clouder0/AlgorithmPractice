#include <cstdio>
int spd[6], w[6], start[6][6], width[6][6];
int num[360], allnum[360];
int main()
{
    for (int i = 1; i <= 5; ++i)
    {
        scanf("%d", spd + i);
        scanf("%d", w + i);
        for (int j = 1; j <= w[i]; ++j) scanf("%d%d", start[i] + j, width[i] + j), start[i][j] %= 360;
    }
    for (int tnt = 0; tnt <= 360; ++tnt)
    {
        for (int i = 0; i < 360; ++i) allnum[i] = 0;
        for (int i = 1; i <= 5; ++i)
        {
            for (int j = 0; j < 360; ++j) num[j] = 0;
            for (int j = 1; j <= w[i]; ++j)
                for (int t = 0; t <= width[i][j]; ++t) num[(t + start[i][j]) % 360] |= 1;
            for (int j = 0; j < 360; ++j) allnum[j] += num[j];
        }
        for (int i = 0; i < 360; ++i)
            if (allnum[i] == 5)
            {
                printf("%d\n", tnt);
                return 0;
            }
        for (int i = 1; i <= 5; ++i) for(int j = 1;j<=w[i];++j) start[i][j] = (start[i][j] + spd[i]) % 360;
    }
    puts("none");
    return 0;
}