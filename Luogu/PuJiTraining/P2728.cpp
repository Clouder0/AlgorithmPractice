#include <cstdio>
int spd[6], w[6], start[6][6], width[6][6];
int now[6];
int isIn(int pos, int st, int w)
{
    if (st + w >= 360)
    {
        return pos >= st || pos <= st + w - 360;
    }
    return pos >= st && pos <= st + w;
}
int main()
{
    for (int i = 1; i <= 5; ++i)
    {
        scanf("%d", spd + i);
        scanf("%d", w + i);
        for (int j = 1; j <= w[i]; ++j) scanf("%d%d", start[i] + j, width[i] + j), start[i][j] %= 360;
    }
    for (int t = 0; t <= 360; ++t)
    {
        int num = 0;
        for (int i = 1; i <= 5; ++i)
        {
            int flag = 0;
            for (int j = 1; !flag && j <= w[i]; ++j)
                flag |= isIn(now[i], start[i][j], width[i][j]);
            num += flag;
        }
        printf("t=%d\n",t);
        for(int i = 1;i<=5;++i) printf("%d ",now[i]);
        puts("");
        if(num == 5) {
            printf("%d\n", t);
            return 0;
        }
        for (int i = 1; i <= 5; ++i) now[i] = (now[i] + spd[i]) % 360;
    }
    puts("none");
    return 0;
}