#include <cstdio>
#include <cstring>
template <typename T>
inline T max(const T &a, const T &b) { return a > b ? a : b; }
template <typename T>
inline T min(const T &a, const T &b) { return a < b ? a : b; }
template <typename T>
void read(T &r)
{
    static char c;
    r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar())
        ;
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar())
        ;
}
const int maxn = 1e4 + 10;
int n, m, k;
int x[maxn], y[maxn];
int bottom[maxn], top[maxn];
int f[maxn][2100];
int main()
{
    read(n);
    read(m);
    read(k);
    for (int i = 1; i <= n; ++i)
        read(x[i]), read(y[i]);
    memset(f, 0x3f, sizeof(f));
    memset(f[1], 0, sizeof(f[1]));
    for (int i = 1; i <= n + 5; ++i)
        bottom[i] = 0, top[i] = 1 << 30;
    for (int i = 1; i <= k; ++i)
    {
        int p;
        read(p);
        read(bottom[p + 1]);
        read(top[p + 1]);
    }
    int last = 0;
    for (int i = 2; i <= n + 1; ++i)
    {
        for (int j = x[i - 1]; j <= m + x[i - 1]; ++j)
                f[i][j] = min(f[i][j - x[i - 1]] + 1, f[i - 1][j - x[i - 1]] + 1);
        for (int j = m + 1; j <= x[i - 1] + m; ++j)
            f[i][m] = min(f[i][m], f[i][j]);
        for (int j = m - y[i - 1]; j >= 0; --j)
                f[i][j] = min(f[i][j], f[i - 1][j + y[i - 1]]);
        for(int j = 0;j<=bottom[i];++j)
            f[i][j] = 1<<30;
        for(int j = top[i];j<=m;++j)
            f[i][j] = 1<<30;
        bool flag = false;
        for (int j = 0; !flag && j <= m; ++j)
            if (f[i][j] < 10000000)
                flag = true;
        if (!flag)
        {
            puts("0");
            printf("%d", last);
            return 0;
        }
        if (!(bottom[i] == 0 && top[i] == 1 << 30))
            ++last;
    }
    puts("1");
    int ans = 1 << 30;
    for (int i = 0; i <= m; ++i)
        if (i > bottom[n + 1] && i < top[n + 1])
            ans = min(ans, f[n + 1][i]);
    printf("%d", ans);
    return 0;
}