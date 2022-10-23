#include <cstdio>
#include <cstring>
template <typename T>
inline T max(const T &a, const T &b) { return a > b ? a : b; }
template <typename T>
void read(T &r)
{
    static char c;
    static int flag;
    flag = 1, r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar())
        if (c == '-')
            flag = -1;
    ;
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar())
        ;
    r *= flag;
}
const int maxn = 410;
const int maxm = 401000;
int n;
int a[maxn], b[maxn];
int f[(maxm << 1) + 1000];
int main()
{
    read(n);
    int maxa = 0, mina = 0;
    for (int i = 1; i <= n; ++i)
        read(a[i]), read(b[i]), maxa += (a[i] > 0 ? a[i] : 0), mina += (a[i] < 0 ? a[i] : 0);
    memset(f, ~0x3f, sizeof(f));
    f[maxm] = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (a[i] > 0)
        {
            for (int j = maxa + maxm; j >= mina + maxm; --j)
                f[j] = max(f[j], f[j - a[i]] + b[i]);
        }
        else
        {
            for (int j = mina + maxm; j <= a[i] + maxa + maxm; ++j)
                f[j] = max(f[j], f[j - a[i]] + b[i]);
        }
    }
    int ans = 1 << 31;
    for (int i = maxm; i <= maxa + maxm; ++i)
        if (f[i] >= 0 && i - maxm + f[i] > ans)
            ans = i - maxm + f[i];
    printf("%d", ans);
    return 0;
}