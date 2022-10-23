#include <cstdio>
using namespace std;
int n, ans;
int all[50];
bool c[100], zl[100], yl[100];
void dfs(short now)
{
    if (now == n + 1)
    {
        if (++ans <= 3)
        {
            for (int i = 1; i <= n; ++i)
                printf("%d ", all[i]);
            printf("\n");
        }
        return;
    }
    for (int i = 1; i <= n; ++i)
    {
        if (zl[now - i] || yl[now + i] || c[i])
            continue;
        all[now] = i;
        zl[now - i] = yl[now + i] = c[i] = true;
        dfs(now + 1);
        zl[now - i] = yl[now + i] = c[i] = false;
    }
}
int main()
{
    scanf("%d", &n);
    dfs(1);
    printf("%d", ans);
    return 0;
}