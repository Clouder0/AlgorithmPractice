#include <cstdio>
#include <algorithm>
#include <cstring>
const int maxn = 100;
char s[maxn];
int n, maxx[maxn];
long long f[maxn][2][maxn][2];
long long dfs(int now, int top, int prenum, int flag)
{
    if(f[now][top][prenum][flag] != -1) return f[now][top][prenum][flag];
    if(now == 0) return f[now][top][prenum][flag] = flag;
    int up = std::min(1, top ? maxx[now] : 1);
    long long res = 0;
    for (int i = 0; i <= up; ++i)
    {
        res += dfs(now - 1, top && i == maxx[now], i == 0 ? 0 : prenum + 1, flag || (i == 0 ? 0 : prenum + 1) >= 3);
    }
    return f[now][top][prenum][flag] = res;
}
int main()
{
    scanf("%s", s + 1);
    n = strlen(s + 1);
    for (int i = 1; i <= n; ++i) maxx[n-i+1] = s[i] - '0';
    memset(f,-1,sizeof(f));
    long long res = 0;
    res = dfs(n, 1, 0, 0);
    printf("%lld\n", res);
    return 0;
}