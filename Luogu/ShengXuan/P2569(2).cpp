#include <cstdio>
#include <memory.h>
using namespace std;
template <typename T>
void read(T& r)
{
    static char c;
    r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar());
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar());
}
template <typename T>
const T max(const T& a, const T& b)
{
    return a > b ? a : b;
}
const int maxn = 2e3 + 10;
int n, maxp, w;
int ap, as, bp, bs;
int dp[maxn][maxn];
int q[maxn], head = 1, tail;
int main()
{
    read(n);
    read(maxp);
    read(w);
    memset(dp, ~0x3f, sizeof(dp));
    for (int i = 1; i <= n; ++i)
    {
        read(ap);
        read(bp);
        read(as);
        read(bs);
        for (int j = 0; j <= as; ++j)
            dp[i][j] = max(dp[i][j], -(ap * j));
        for (int j = 0; j <= maxp; ++j)
            dp[i][j] = max(dp[i][j], dp[i - 1][j]);
        if (i <= w)
            continue;
        head = 1, tail = 0;
        //max[j-ba,j] ->j
        for (int j = 0; j <= maxp; ++j)
        {
            while (tail >= head && dp[i - w - 1][j] + j * ap >= dp[i - w - 1][q[tail]] + q[tail] * ap)
                --tail;
            q[++tail] = j;
            while (tail >= head && q[head] < j - as)
                ++head;
            if (tail >= head)
                dp[i][j] = max(dp[i][j], dp[i - w - 1][q[head]] + q[head] * ap - j * ap);
        }
        //max[j,j+sa] -> j
        head = 1, tail = 0;
        for (int j = maxp; j >= 0; --j)
        {
            while (tail >= head && dp[i - w - 1][j] + j * bp >= dp[i - w - 1][q[tail]] + q[tail] * bp)
                --tail;
            q[++tail] = j;
            while (tail >= head && q[head] > j + bs)
                ++head;
            if (tail >= head)
                dp[i][j] = max(dp[i][j], dp[i - w - 1][q[head]] + q[head] * bp - j * bp);
        }
    }
    printf("%d", dp[n][0]);
    return 0;
}