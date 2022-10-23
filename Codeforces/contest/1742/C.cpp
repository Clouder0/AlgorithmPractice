#include <cstdio>

int T, num;
char s[10][10];
int main()
{
    scanf("%d", &T);
    while (T--)
    {
        for (int i = 1; i <= 8; ++i) scanf("%s", s[i] + 1);
        for (int i = 1; i <= 8; ++i)
        {
            num = 0;
            for (int j = 1; j <= 8; ++j) num += (s[i][j] == 'R');
            if (num == 8) goto red;
            num = 0;
            for (int j = 1; j <= 8; ++j) num += (s[j][i] == 'B');
            if (num == 8) goto blue;
        }
    blue:
        puts("B");
        continue;
    red:
        puts("R");
        continue;
    }
    return 0;
}