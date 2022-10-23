#include <cstdio>
#include <cstring>
using namespace std;
const int mod = 1000000007;
const int maxn = 710;
char s[maxn];
int f[maxn][maxn][3][3];
inline int add(int a,int b)
{
    int res = a + b;
    if(res >= mod) res -= mod;
    return res;
}
int match[maxn],st[maxn],top;
bool vis[maxn][maxn];
void dfs(int l,int r)
{
    if(vis[l][r]) return;
    vis[l][r] = 1;
    if(l + 1 == r) return (void)(f[l][r][0][1] = f[l][r][1][0] = f[l][r][2][0] = f[l][r][0][2] = 1);
    if(match[l] == r)
    {
        dfs(l + 1,r - 1);
        for (int i = 0; i <= 2; ++i)
            for (int j = 0; j <= 2; ++j)
            {
                if (j != 1) f[l][r][0][1] = add(f[l][r][0][1], f[l + 1][r - 1][i][j]);
                if (j != 2) f[l][r][0][2] = add(f[l][r][0][2], f[l + 1][r - 1][i][j]);
                if (i != 1) f[l][r][1][0] = add(f[l][r][1][0], f[l + 1][r - 1][i][j]);
                if (i != 2) f[l][r][2][0] = add(f[l][r][2][0], f[l + 1][r - 1][i][j]);
            }
    }
    else
    {
        dfs(l,match[l]),dfs(match[l] + 1,r);
        for (int i = 0; i <= 2; ++i)
            for (int j = 0; j <= 2; ++j)
                for (int x = 0; x <= 2; ++x)
                    for (int y = 0; y <= 2; ++y)
                    {
                        if(j && j == x) continue;
                        if(i && j) continue;
                        f[l][r][i][y] = add(f[l][r][i][y], (1ll * f[l][match[l]][i][j] * f[match[l] + 1][r][x][y]) % mod);
                    }
    }
}
int main()
{
    scanf("%s",s + 1);
    int n = strlen(s + 1);
    for (int i = 1; i <= n; ++i) if(s[i] == '(') st[++top] = i; else match[i] = st[top],match[st[top--]] = i;
    dfs(1,n);
    long long ans = 0;
    for (int i = 0; i <= 2; ++i) for (int j = 0; j <= 2; ++j) ans = add(ans, f[1][n][i][j]);
    printf("%lld\n", ans);
    return 0;
}