#include <cstdio>
const int maxn = 4e4 + 100;
int n, m, w[maxn], v[maxn], num[maxn];
long long f[maxn];
template <typename T>
inline T _max(const T& a, const T& b)
{
    return a > b ? a : b;
}
void upd(int weight, long long value)
{
    for (int j = m; j >= weight; --j) f[j] = _max(f[j], f[j - weight] + value);
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%d%d%d", v + i, w + i, num + i);
    for (int i = 1; i <= n; ++i) 
    {
        int left = num[i];
        for (int j = 1; j <= left; j <<= 1) upd(w[i] * j, v[i] * j), left -= j;
        if (left) upd(w[i] * left, v[i] * left);
    }
    long long maxx = 0;
    for (int i = 1; i <= m; ++i) maxx = _max(maxx, f[i]);
    printf("%lld\n", maxx);
    return 0;
}