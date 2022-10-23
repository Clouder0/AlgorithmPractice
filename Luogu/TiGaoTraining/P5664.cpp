#include <cstdio>
#include <cstring>
using namespace std;
inline void read(int &r)
{
    static char c;r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar());
    for (; c <= '9' && c >= '0';r = (r << 3) + (r << 1) + (c ^ 48), c = getchar());
}
const int mod = 998244353;
const int maxn = 110;
const int maxm = 2100;
int n,m;
int a[maxn][maxm];
long long f[maxn][maxn<<1];
long long g[maxn][maxn];
int s[maxn][maxm];
int main()
{
    read(n);
    read(m);

    for(int i = 1;i<=n;++i)
        for(int j = 1;j<=m;++j)
            read(a[i][j]),s[i][0] = (s[i][0] + a[i][j]) % mod;
    for(int i = 1;i<=n;++i)
        for(int j = 1;j<=m;++j)
            s[i][j] = (s[i][0] - a[i][j]) % mod;
    long long res = 0;
    for (int col = 1; col <= m; ++col)
    {
        memset(f,0,sizeof(f));
        f[0][n] = 1;// f[i][j+n]
        for(int i = 1;i<=n;++i)
            for(int j = n - i;j<=n+i;++j)
                f[i][j] = (f[i-1][j] + (f[i-1][j+1] * s[i][col]) % mod + (f[i-1][j-1] * a[i][col]) % mod) % mod;
        for(int i = 1;i<=n;++i)
            res  = (res + f[n][n+i]) % mod;
    }
    for(int i = 0;i<=n;++i)
        g[i][0] = 1;
    for(int i = 1;i<=n;++i)
        for(int j = 1;j<=n;++j)
            g[i][j] = (g[i-1][j] + g[i-1][j-1] * s[i][0]) % mod;
    for(int i = 1;i<=n;++i)
        res = (res - g[n][i] + mod) % mod;
    printf("%lld",(res*(mod-1)) % mod);
    return 0;
}