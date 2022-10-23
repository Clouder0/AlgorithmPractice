#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 2e5 + 100;
const int mod = 1e9 + 7;
int n;
char s[maxn];
inline int add(int x,int y)
{
    int res = x + y;
    if(res >= mod) res -= mod;
    if(res < 0) res += mod;
    return res;
}
inline int mul(int x, int y) { return (1ll * x * y) % mod; }
int f[maxn][4][4];
int tp[maxn];
int main()
{
    scanf("%d %s", &n,s + 1);
    int num = 0;
    tp[0] = 1;
    for (int i = 1; i <= n; ++i) num += s[i] == '?', tp[i] = mul(3, tp[i - 1]);
    f[1][0][0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 0; j <= 3; ++j)
        {
            for (int k = 0; k <= 3; ++k)
            {
                if(!f[i][j][k]) continue;
                f[i + 1][j][k] = add(f[i + 1][j][k], f[i][j][k]);
                if (j < 3)
                {
                    if (s[i] == 'a' + j) f[i + 1][j + 1][k] = add(f[i + 1][j + 1][k], f[i][j][k]);
                    else if (s[i] == '?') f[i + 1][j + 1][k + 1] = add(f[i + 1][j + 1][k + 1], f[i][j][k]);
                }
            }
        }
    }
    int ans = 0;
    for (int i = 0; i <= 3; i++)
        if (num >= i) ans = add(ans, mul(f[n + 1][3][i], tp[num - i]));
    printf("%d\n", ans);
    return 0;
}