#include <cstdio>
#include <cstring>
const int maxn = 110;
char s[maxn];
int num[maxn], n, k;
long long f[maxn][4][2][2];
long long dfs(int pos, int limit, int zero, int sum)
{
    if (sum > k) return 0;
    if (f[pos][sum][limit][zero] != -1) return f[pos][sum][limit][zero];
    if (pos == n + 1) return sum == k;
    int up = limit ? num[pos] : 9;
    long long res = 0;
    for (int i = 0; i <= up; ++i) res += dfs(pos + 1, i == up && limit, zero && !i, sum + (i > 0));
    return f[pos][sum][limit][zero] = res;
}
int main()
{
    scanf("%s\n%d", s + 1, &k);
    memset(f, -1, sizeof(f));
    n = std::strlen(s + 1);
    for (int i = 1; i <= n; ++i) num[i] = s[i] - '0';
    printf("%lld\n", dfs(0, 1, 1, 0));
    return 0;
}