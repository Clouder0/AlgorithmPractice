#include <algorithm>
#include <cstdio>
using namespace std;
const int maxn = 2e5 + 100;
int n, a[maxn], cur[maxn], top;
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    for (int i = 1; i <= n; ++i)
    {
        int p = lower_bound(cur + 1, cur + 1 + top, a[i]) - cur;
        cur[p] = a[i];
        if (p > top) top = p;
    }
    printf("%d\n", top);
    return 0;
}