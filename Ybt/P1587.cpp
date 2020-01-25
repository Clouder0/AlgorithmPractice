#include <cstdio>
#include <memory.h>
using namespace std;
template <typename T>
void read(T &r)
{
    static char c;r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar());
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar());
}
int A, B;
long long dp[100][100];
int num[100];
long long dfs(int pos, int lead, int limit, int last)
{
    if (pos == 0)
        return dp[pos][last] = !lead;
    if (!lead && !limit && dp[pos][last] != -1)
        return dp[pos][last];
    int up = limit ? num[pos] : 9;
    int ans = 0;
    for (int i = 0; i <= up; ++i)
        if (last - i >= 2 || i - last >= 2 || lead)
            ans += dfs(pos - 1, i == 0 && lead, i == num[pos] && limit, i);
    if (!limit && !lead)
        dp[pos][last] = ans;
    return ans;
}
long long solve(int x)
{
    memset(dp, -1, sizeof(dp));
    int cnt;
    for (cnt = 0; x; num[++cnt] = x % 10, x /= 10);
    return dfs(cnt, true, true, 0);
}
int main()
{
    read(A);
    read(B);
    printf("%lld", solve(B) - solve(A - 1));
    return 0;
}