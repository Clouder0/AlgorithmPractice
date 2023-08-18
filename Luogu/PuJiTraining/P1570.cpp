#include <algorithm>
#include <cstdio>
const int maxn = 1100;
int n, m;
struct node
{
    int v, c;
} A[maxn];
double now;
bool cmp(const node& a, const node& b)
{
    return a.c * now - a.v < b.c * now - b.v;
}
const double EPS = 1e-7;
bool check()
{
    std::sort(A + 1, A + 1 + n, cmp);
    double sum = 0;
    for (int i = 1; i <= m; ++i) sum += A[i].c * now - A[i].v;
    return sum <= 0;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%d", &A[i].v);
    for (int i = 1; i <= n; ++i) scanf("%d", &A[i].c);
    double l = 0, r = 1000, mid, ans;
    while (r - l > EPS)
    {
        mid = (l + r) / 2;
        now = mid;
        if (check())
        {
            ans = mid;
            l = mid;
        }
        else
        {
            r = mid;
        }
    }
    printf("%.3f", ans);
    return 0;
}