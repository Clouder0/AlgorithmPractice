#include <cstdio>
using namespace std;
int n;
int main()
{
    scanf("%d", &n);
    int ans = 0;
    for (int l = 1, r; l <= n; l = r + 1)
    {
        r = n / (n / l);
        ans += (n / l) * (r - l + 1);
    }
    printf("%d", ans);
    return 0;
}