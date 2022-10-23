#include <cstdio>
#include <algorithm>
using namespace std;
struct node
{
    int a, b;
    bool operator<(const node &b)
    {
        if (this->b != b.b)
            return this->b > b.b;
        return this->a < b.a;
    }
} all[5010];
int n, m;
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%d%d", &all[i].a, &all[i].b);
    sort(all + 1, all + 1 + n);
    m *= 1.5;
    int point = all[m].b, cnt = 0;
    for (int i = 1; all[i].b >= point; ++i)
        ++cnt;
    printf("%d %d\n", point, cnt);
    for (int i = 1; all[i].b >= point; ++i)
        printf("%d %d\n", all[i].a, all[i].b);
    return 0;
}