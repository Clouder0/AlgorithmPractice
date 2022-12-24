#include <cstdio>
const int maxn = 40;
int n, m;
char s[maxn][maxn];
int num[maxn];
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%s", s[i] + 1);
    int num = 0;
    for (int i = 2; i <= n; ++i)
        for (int j = 1; j < i; ++j)
        {
            int can = 0;
            for (int k = 1; k <= m; ++k) can += (s[i][k] == 'o' || s[j][k] == 'o');
            num += (can == m);
        }
    printf("%d\n", num);
    return 0;
}