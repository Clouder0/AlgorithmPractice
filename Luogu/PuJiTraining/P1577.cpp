#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1e4 + 100;
const double EPS = 1e-8;
int n, k;
double L[maxn];
bool check(double len)
{
    int cut = 0;
    for (int i = 1; i <= n && cut < k; ++i) cut += (int)(L[i] / len);
    // printf("%.2f %d\n",len,cut);
    return cut >= k;
}
int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i) scanf("%lf", L + i);
    std::sort(L + 1, L + n + 1);
    double l = 0, r = L[n], mid, ans;
    while (r - l > EPS)
    {
        mid = (l + r) / 2;
        if (check(mid))
            l = mid, ans = mid;
        else
            r = mid;
    }
    printf("%.8f\n", ans);
    return 0;
}