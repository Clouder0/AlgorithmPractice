#include <cstdio>
using namespace std;
int n;
long long sa[31][31];
int root[31][31];
void dfs(int l, int r)
{
    if (l > r)
    {
        sa[l][r] = 1;
        return;
    }
    if (sa[l][r])
        return;
    long long t;
    for (int i = l; i <= r; ++i)
    {
        //决定i当根节点的情况
        dfs(l, i - 1);
        dfs(i + 1, r);
        t = sa[l][i - 1] * sa[i + 1][r] + sa[i][i];
        if (t > sa[l][r])
        {
            sa[l][r] = t;
            root[l][r] = i;
        }
    }
    return;
}
void output(int l, int r)
{
    if (!root[l][r])
        return;
    printf("%d ", root[l][r]);
    output(l, root[l][r] - 1);
    output(root[l][r] + 1, r);
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &sa[i][i]), root[i][i] = i;
    //每次就是决定谁来当根节点
    dfs(1, n);
    printf("%lld\n", sa[1][n]);
    output(1, n);
    return 0;
}