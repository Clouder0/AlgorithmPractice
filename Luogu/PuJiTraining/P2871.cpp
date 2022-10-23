#include <cstdio>
const int maxn = 1e5 + 100;
int n, m, w[maxn], v[maxn], f[maxn];
inline int _max(const int& a, const int& b) { return a > b ? a : b; }
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%d%d", w + i, v + i);
    for (int i = 1; i <= n; ++i)
        for (int j = m; j >= w[i]; --j) f[j] = _max(f[j], f[j - w[i]] + v[i]);
    int maxx = 0;
    for (int i = 0; i <= m; ++i) maxx = _max(maxx, f[i]);
    printf("%d\n", maxx);
    return 0;
}