#include <cstdio>
const int maxn = 1e3 + 100;
int n;
int to[maxn * maxn][4];
int main()
{
    scanf("%d", &n);
    int start = 0;
    for (int i = 1; i <= n * n; ++i)
    {
        for (int j = 0; j < 4; ++j) scanf("%d", to[i] + j);
        if(to[i][0] == -1 && to[i][2] == -1) start = i;
    }
    if(n == 1) 
    {
        puts("1");
        return 0;
    }
    for (int i = 1; i <= n; ++i)
    {
        printf("%d ", start);
        int p = to[start][3];
        for (int j = 2; j < n; ++j)
        {
            printf("%d ", p);
            p = to[p][3];
        }
        printf("%d", p);
        start = to[start][1];
        if(i != n) puts("");
    }
    return 0;
}