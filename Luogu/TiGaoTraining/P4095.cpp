#include <cstdio>
template <typename T>
inline T min(const T &a, const T &b) { return a < b ? a : b; }
template <typename T>
inline T max(const T &a, const T &b) { return a > b ? a : b; }
template <typename T>
void read(T &r)
{
    static char c;
    r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar());
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar());
}
const int maxn = 1e3 + 10;
int n, q;
int w[maxn], v[maxn], c[maxn];
int f1[maxn][maxn], f2[maxn][maxn];
int main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
        read(w[i]), read(v[i]), read(c[i]);
    for (int i = 1; i <= n; ++i)
    {
        for(int j = 1;j<=1000;++j)
            f1[i][j] = f1[i-1][j];
        int k, maxx;
        for (maxx = c[i], k = 1; k <= maxx; maxx -= k, k <<= 1)
        {
            int weight = w[i] * k, value = v[i] * k;
            for (int j = 1000; j >= weight; --j)
                f1[i][j] = max(f1[i][j], f1[i][j - weight] + value);
        }
        if (maxx)
        {
            int weight = w[i] * maxx, value = v[i] * maxx;
            for (int j = 1000; j >= weight; --j)
                f1[i][j] = max(f1[i][j], f1[i][j - weight] + value);
        }
    }
    for (int i = n; i; --i)
    {
        for (int j = 1; j <= 1000; ++j)
            f2[i][j] = f2[i + 1][j];
        int k, maxx;
        for (maxx = c[i], k = 1; k <= maxx; maxx -= k, k <<= 1)
        {
            int weight = w[i] * k, value = v[i] * k;
            for (int j = 1000; j >= weight; --j)
                f2[i][j] = max(f2[i][j], f2[i][j - weight] + value);
        }
        if (maxx)
        {
            int weight = w[i] * maxx, value = v[i] * maxx;
            for (int j = 1000; j >= weight; --j)
                f2[i][j] = max(f2[i][j], f2[i][j - weight] + value);
        }
    }
    read(q);
    int d, e;
    while (q--)
    {
        read(d);
        read(e);
        ++d;
        int ans = 0;
        for (int i = 0; i <= e; ++i)
            ans = max(ans, f1[d - 1][i] + f2[d + 1][e - i]);
        printf("%d\n", ans);
    }
    return 0;
}