#include <cstdio>
#include <cstring>
using namespace std;
char all[510];
int num[510];
int dp[510];
int f[510];
int n;
inline int max(const int &a, const int &b)
{
    return a > b ? a : b;
}
int cmp(int l1, int r1, int l2, int r2)
{
    while (num[l1] == 0)
        ++l1;
    while (num[l2] == 0)
        ++l2;
    if (r1 < l1 || r2 < l2)
        return false;
    if (r1 - l1 != r2 - l2)
        return r1 - l1 > r2 - l2;
    for (int i = 0; i <= r1 - l1; ++i)
        if (num[l1 + i] != num[l2 + i])
            return num[l1 + i] > num[l2 + i];
    return false;
}
int main()
{
    scanf("%s", all + 1);
    n = strlen(all + 1);
    for (int i = 1; i <= n; ++i)
        num[i] = all[i] - '0', dp[i] = 1;

    for (int i = 1; i <= n; ++i)
    {
        for (int j = i; j; --j)
        {
            if (cmp(j, i, dp[j - 1], j - 1))
            {
                dp[i] = max(dp[i], j);
                break;
            }
        }
    }

    int zero = dp[n] - 1;
    while (num[zero] == 0 && zero)
        f[zero--] = n;

    f[dp[n]] = n;
    for (int i = dp[n] - 1; i; --i)
    {
        for (int j = dp[n] - 1; j >= i; --j)
        {
            if (cmp(j + 1, f[j + 1], i, j))
            {
                f[i] = j;
                break;
            }
        }
    }

    int p = 1;
    for (int i = p; i <= f[p]; ++i)
            putchar(num[i] + '0');
    p = f[p] + 1;
    while (p <= n)
    {
        putchar(',');
        for (int i = p; i <= f[p]; ++i)
            putchar(num[i] + '0');
        p = f[p] + 1;
    }
    return 0;
}