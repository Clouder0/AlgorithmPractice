#include <cstdio>
#include <algorithm>
using namespace std;
struct node
{
    int price, num;
} all[5001];
int n, m;
bool cmp(const node &a, const node &b)
{
    return a.price < b.price;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
        scanf("%d %d", &all[i].price, &all[i].num);
    sort(all + 1, all + 1 + m, cmp);
    int ans = 0;
    for(int i = 1;i<=m;++i)
    {
        if(n <= all[i].num)
        {
            ans += all[i].price * n;
            break;
        }
        ans += all[i].price * all[i].num;
        n -= all[i].num;
    }
    printf("%d",ans);
    return 0;
}