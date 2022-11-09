#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;
const int maxn = 2e5 + 100;
int T, n, a[maxn];
int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) scanf("%d", a + i);
        sort(a + 1, a + 1 + n);
        int maxx = 0;
        for (int i = 3; i <= n; ++i) maxx = max(maxx, a[i] - a[i - 1] + a[i] - a[1]);
        for (int i = 1; i <= n - 2; ++i) maxx = max(maxx, a[i + 1] - a[i] + a[n] - a[i]);
        printf("%d\n",maxx);
    }
    return 0;
}