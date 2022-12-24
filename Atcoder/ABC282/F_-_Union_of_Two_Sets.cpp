#include <cstdio>

const int maxn = 4100;
int n, lg[maxn];
int cnt, st[maxn][15];
int L[51000], R[51000];
int main()
{
    scanf("%d",&n);
    lg[1] = 0;
    for (int i = 2; i <= n; ++i) lg[i] = lg[i >> 1] + 1;
    for (int i = 1; i <= n; ++i)
        for (int j = 0; i + (1 << j) - 1 <= n; ++j) st[i][j] = ++cnt, L[cnt] = i, R[cnt] = i + (1 << j) - 1;
    printf("%d\n", cnt);
    for (int i = 1; i <= cnt; ++i) printf("%d %d\n", L[i], R[i]);
    fflush(stdout);
    int q;
    scanf("%d",&q);
    while(q--)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        int len = lg[r - l + 1];
        printf("%d %d\n", st[l][len], st[r - (1 << len) + 1][len]);
        fflush(stdout);
    }
    return 0;
}