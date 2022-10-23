#include <cstdio>
#include <cstring>
using namespace std;
int col, k, n;
char s[260];
bool num[10][10];
void init()
{
    //初始化
    /* 
    这是一个数字的七个标位
     11111 
    2     3
    2     3
    2     3
    2     3
    2     3
     44444 
    5     6
    5     6
    5     6
    5     6
    5     6
     77777 
    */

    num[1][1] = false;
    num[1][2] = false;
    num[1][3] = true;
    num[1][4] = false;
    num[1][5] = false;
    num[1][6] = true;
    num[1][7] = false;

    num[2][1] = true;
    num[2][2] = false;
    num[2][3] = true;
    num[2][4] = true;
    num[2][5] = true;
    num[2][6] = false;
    num[2][7] = true;

    num[3][1] = true;
    num[3][2] = false;
    num[3][3] = true;
    num[3][4] = true;
    num[3][5] = false;
    num[3][6] = true;
    num[3][7] = true;

    num[4][1] = false;
    num[4][2] = true;
    num[4][3] = true;
    num[4][4] = true;
    num[4][5] = false;
    num[4][6] = true;
    num[4][7] = false;

    num[5][1] = true;
    num[5][2] = true;
    num[5][3] = false;
    num[5][4] = true;
    num[5][5] = false;
    num[5][6] = true;
    num[5][7] = true;

    num[6][1] = true;
    num[6][2] = true;
    num[6][3] = false;
    num[6][4] = true;
    num[6][5] = true;
    num[6][6] = true;
    num[6][7] = true;

    num[7][1] = true;
    num[7][2] = false;
    num[7][3] = true;
    num[7][4] = false;
    num[7][5] = false;
    num[7][6] = true;
    num[7][7] = false;

    num[8][1] = true;
    num[8][2] = true;
    num[8][3] = true;
    num[8][4] = true;
    num[8][5] = true;
    num[8][6] = true;
    num[8][7] = true;

    num[9][1] = true;
    num[9][2] = true;
    num[9][3] = true;
    num[9][4] = true;
    num[9][5] = false;
    num[9][6] = true;
    num[9][7] = true;

    num[0][1] = true;
    num[0][2] = true;
    num[0][3] = true;
    num[0][4] = false;
    num[0][5] = true;
    num[0][6] = true;
    num[0][7] = true;
}
int main()
{
    scanf("%d", &k);
    scanf("%s", s + 1);
    init();
    n = strlen(s + 1);
    //打印第一行
    for (int i = 1; i <= n; ++i)
    {
        putchar(' ');
        if (num[s[i] - '0'][1])
            for (int j = 1; j <= k; ++j)
                putchar('-');
        else
            for (int j = 1; j <= k; ++j)
                putchar(' ');
        putchar(' ');

        putchar(' ');
    }
    putchar('\n'); //换行
    for (int p = 1; p <= k; ++p)
    {
        for (int i = 1; i <= n; ++i)
        {
            if (num[s[i] - '0'][2])
                putchar('|');
            else
                putchar(' ');

            for (int j = 1; j <= k; ++j)
                putchar(' ');

            if (num[s[i] - '0'][3])
                putchar('|');
            else
                putchar(' ');

            putchar(' ');
        }
        putchar('\n');
    }
    //打印中间行
    for (int i = 1; i <= n; ++i)
    {
        putchar(' ');
        if (num[s[i] - '0'][4])
        {
            for (int j = 1; j <= k; ++j)
                putchar('-');
        }
        else
        {
            for (int j = 1; j <= k; ++j)
                putchar(' ');
        }
        putchar(' ');

        putchar(' ');
    }
    putchar('\n');
    for (int p = 1; p <= k; ++p)
    {
        for (int i = 1; i <= n; ++i)
        {
            if (num[s[i] - '0'][5])
                putchar('|');
            else
                putchar(' ');

            for (int j = 1; j <= k; ++j)
                putchar(' ');

            if (num[s[i] - '0'][6])
                putchar('|');
            else
                putchar(' ');

            putchar(' ');
        }
        putchar('\n');
    }
    //末尾行
    for (int i = 1; i <= n; ++i)
    {
        putchar(' ');
        if (num[s[i] - '0'][7])
            for (int j = 1; j <= k; ++j)
                putchar('-');
        else
            for (int j = 1; j <= k; ++j)
                putchar(' ');
        putchar(' ');

        putchar(' ');
    }
    return 0;
}