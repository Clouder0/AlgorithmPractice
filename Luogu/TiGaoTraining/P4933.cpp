#include <cstdio>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 1010;
const int maxv = 2e4 + 10;
const int mod = 998244353;
int n;
int h[maxn];
int f[maxn][maxv << 2];
long long ans = 0;
int main()
{
    read(n);
    for(int i = 1;i<=n;++i)
        read(h[i]);
    for(int i = 1;i<=n;++i)
    {
        for(int j = i-1;j;--j)
        {
            f[i][h[i] - h[j] + maxv] = (f[i][h[i] - h[j] + maxv] + f[j][h[i] - h[j] + maxv] + 1) % mod;
            ans = (ans + f[j][h[i] - h[j] + maxv] + 1) % mod;
        }
    }
    printf("%lld",(ans + n) % mod);
    return 0;
}