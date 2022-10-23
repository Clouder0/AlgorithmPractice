#include <cstdio>
#include <cstring>
template <typename T>
inline T _min(const T &a, const T &b) { return a < b ? a : b; }
template <typename T>
void read(T &r)
{
    static char c;
    r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar());
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar());
}
const int maxn = 510;
const int maxt = 4e6 + 10;
int n, m, T;
int a[maxn];
int sum[maxt], cnt[maxt];
int f[maxt];
int main()
{
    read(n);
    read(m);
    for (int i = 1; i <= n; ++i)
        read(a[i]), sum[a[i]] += a[i], cnt[a[i]]++, T = (a[i] > T ? a[i] : T);
    T += m;
    for (int i = 1; i <= T; ++i)
        sum[i] += sum[i - 1], cnt[i] += cnt[i - 1];
    for (int i = 0; i <= T; ++i)
    {
        f[i] = cnt[i] * i - sum[i];
        for (int j = i - m; j >= i - m * 2 && j >= 0; --j)
            f[i] = _min(f[i], f[j] + (cnt[i] - cnt[j]) * i - sum[i] + sum[j]);
    }
    int ans = 1 << 30;
    for (int i = T - m; i < T; ++i)
        ans = _min(f[i], ans);
    printf("%d", ans);
    return 0;
}