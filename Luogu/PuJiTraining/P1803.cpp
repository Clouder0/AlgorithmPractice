#include <cstdio>
#include <algorithm>
using namespace std;
struct node
{
    int l, r;
} all[1000001];
int n,last,ans;
bool cmp(const node &a, const node &b)
{
    return a.r < b.r;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d%d", &all[i].l, &all[i].r);
    sort(all + 1, all + 1 + n, cmp);
    for (int i = 1; i <= n; ++i)
        if (all[i].l >= last && ++ans)
            last = all[i].r;
    printf("%d", ans);
    return 0;
}