#include <cstdio>
int n, k, num;
int all[10];
void dfs(int left, int pos, int last)
{
    if (pos == k && left >= last)
    {
        all[k] = left;
        for(int i = 1;i<=k;++i) printf("%d ",all[i]);
        printf("\n");
        ++num;
        return;
    }
    for (int i = last; i <= left; ++i)
        all[pos] = i, dfs(left - i, pos + 1, i);
}
int main()
{
    scanf("%d%d", &n, &k);
    dfs(n, 1, 1);
    printf("%d\n", num);
    return 0;
}