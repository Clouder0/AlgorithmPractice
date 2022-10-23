#include <cstdio>
#include <cstring>
#include <algorithm>
const int maxn = 40;
int l, r;
int a[maxn], b[maxn], lena, lenb;
int f[maxn][2][2][maxn][maxn];
int dfs(int pos, int lim, int contzero, int prezeros, int ones, int total, int *arr)
{
    if(f[pos][lim][contzero][prezeros][ones] != -1) return f[pos][lim][contzero][prezeros][ones];
    if (pos == total + 1) return total - ones - prezeros >= ones;
    int up = lim ? arr[pos] : 1;
    int res = 0;
    for (int i = 0; i <= up; ++i)
        res += dfs(pos + 1, lim && i == up, contzero && !i, contzero ? prezeros + !i : prezeros, ones + i, total, arr);
    return f[pos][lim][contzero][prezeros][ones] = res;
}
int main()
{
    scanf("%d%d", &l, &r);
    --l;
    while (l) a[++lena] = l & 1, l >>= 1;
    while (r) b[++lenb] = r & 1, r >>= 1;
    std::reverse(a + 1, a + 1 + lena);
    std::reverse(b + 1, b + 1 + lenb);
    std::memset(f, -1, sizeof(f));
    int lnum = dfs(1, 1, 1, 0, 0, lena, a);
    std::memset(f, -1, sizeof(f));
    int rnum = dfs(1, 1, 1, 0, 0, lenb, b);
    printf("%d\n", rnum - lnum);
    return 0;
}