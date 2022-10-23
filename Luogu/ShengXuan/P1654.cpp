#include <cstdio>
const int maxn = 1e5 + 100;
int n;
double p[maxn], f[maxn], g[maxn], h[maxn];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%lf", p + i);
    for (int i = 1; i <= n; ++i)
    {
        f[i] = (f[i - 1] + 1) * p[i];
        g[i] = (g[i - 1] + 2 * f[i - 1] + 1) * p[i];
        h[i] = h[i - 1] + (3 * g[i - 1] + 3 * f[i - 1] + 1) * p[i];
    }
    printf("%.1f",h[n]);
    return 0;
}