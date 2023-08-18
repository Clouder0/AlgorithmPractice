#include <cstdio>
#include <algorithm>
#include <set>
const double EPS = 1e-6;
const int maxn = 2e5 + 100;
int n, a[maxn];
int vals[maxn];
long double f[maxn][2];  // 0 not select i, 1 selected i, max sum - average
int ff[maxn][2];
bool check(long double mid) {
    f[1][0] = 0, f[1][1] = a[1] - mid;
    for (int i = 2; i <= n; ++i)
    {
        f[i][0] = f[i - 1][1];
        f[i][1] = std::max(f[i - 1][1] + a[i] - mid, f[i - 1][0] + a[i] - mid);
    }
    return std::max(f[n][0], f[n][1]) >= 0;
}
bool check2(int mid)
{
    ff[1][0] = 0, ff[1][1] = (a[1] >= mid) ? 1 : -1;
    for (int i = 2; i <= n; ++i)
    {
        ff[i][0] = ff[i - 1][1];
        ff[i][1] = std::max(ff[i - 1][1] + ((a[i] >= mid) ? 1 : -1), ff[i - 1][0] + ((a[i] >= mid) ? 1 : -1));
    }
    return std::max(ff[n][0], ff[n][1]) > 0;
}
int main()
{
    scanf("%d", &n);
    int minn = 1e9, maxx = 0;
    for (int i = 1; i <= n; ++i) scanf("%d", a + i), minn = std::min(minn, a[i]), maxx = std::max(maxx, a[i]);
    double l = minn - 1, r = maxx + 1, mid, ans;
    while (r - l > EPS)
    {
        mid = (l + r) / 2;
        if (check(mid))
            ans = mid, l = mid;
        else
            r = mid;
    }
    printf("%.7f\n", ans);
    for(int i = 1;i<=n;++i) vals[i] = a[i];
    std::sort(vals + 1, vals + 1 + n);
    int ll = 1, rr = n, mmid, anss;
    while (ll <= rr)
    {
        mmid = (ll + rr) / 2;
        if(check2(vals[mmid])) anss = mmid, ll = mmid + 1;
        else rr = mmid - 1;
    }
    printf("%d\n", vals[anss]);
    return 0;
}