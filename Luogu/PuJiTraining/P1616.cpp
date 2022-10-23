#include <cstdio>
const int maxn = 1e7 + 100;
int n, m, w[maxn], v[maxn];
long long f[maxn];
template <typename T>
inline T _max(const T& a, const T& b)
{
    return a > b ? a : b;
}
int main()
{
    scanf("%d%d", &m, &n);
    for (int i = 1; i <= n; ++i) scanf("%d%d", w + i, v + i);
    for (int i = 1; i <= n; ++i)
        for (int j = w[i]; j <= m; ++j) f[j] = _max(f[j], f[j - w[i]] + v[i]);
    long long maxx = 0;
    for (int i = 0; i <= m; ++i) maxx = _max(maxx, f[i]);
    printf("%lld\n", maxx);
    return 0;
}