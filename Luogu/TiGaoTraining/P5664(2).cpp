#include <cstdio>
#include <cstring>
using namespace std;
inline void read(int &r)
{
    static char c;r = 0;
    for(c = getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int mod = 998244353;
const int maxn = 110;
const int maxm = 2100;
int n,m;
long long f[maxn][maxn][maxn];
long long g[maxn][maxn];
long long s[maxn][maxn];
int a[maxn][maxm];
int main()
{
    read(n);
    read(m);
    for(int i = 1;i<=n;++i)
        for(int j = 1;j<=m;++j)
            read(a[i][j]),s[i][0] = (s[i][0] + a[i][j]) % mod;
    for(int i = 1;i<=n;++i)
        for(int j = 1;j<=m;++j)
            s[i][j] = s[i][0] - a[i][j];
    long long res = 0;
    for(int col = 1;col<=m;++col)
    {
        memset(f,0,sizeof(f));
        for(int i = 0;i<=n;++i)
            f[i][0][0] = 1;
        for(int i = 1;i<=n;++i)
            for(int j = 0;j<=i;++j)
                for(int k = 0;j+k<=i;++k)
                {
                    f[i][j][k] = f[i-1][j][k];
                    if(j > 0)
                        f[i][j][k] = (f[i][j][k] + f[i-1][j-1][k] * s[i][col]) % mod;
                    if(k > 0)
                        f[i][j][k] = (f[i][j][k] + f[i-1][j][k-1] * a[i][col]) % mod;
                }
        for(int j = 0;j<=n;++j)
            for(int k = j+1;j+k<=n;++k)
                res = (res + f[n][j][k]) % mod;
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