#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
int t, n, lim, cnt;
int save[50000];
int main()
{
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d", &n);
        lim = sqrt(n);
        cnt = 0;
        for (register int i = 1; i <= lim; ++i)
            save[++cnt] = n / i;
        if (cnt && lim == save[cnt]) //特判，注意有可能输入为0，这样cnt会被减为负数……
            --cnt;
        printf("%d\n", cnt + lim + 1);
        for (int i = 0; i <= lim; ++i)
            printf("%d ", i);
        for (int i = cnt; i; --i)
            printf("%d ", save[i]);
        putchar('\n');
    }
    return 0;
}