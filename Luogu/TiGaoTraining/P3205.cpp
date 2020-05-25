#include <cstdio>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int mod = 19650827;
const int maxn = 1e3 + 10;
int n;
int a[maxn];
int f[maxn][maxn][2];//0 L 1 R
int main()
{
    read(n);
    for(int i = 1;i<=n;++i)
        read(a[i]);
    for(int i = 1;i<=n;++i)
        f[i][i][0] = 1;
    for(int len = 2;len<=n;++len)
    {
        for(int l = 1,r = l + len - 1;r<=n;++l,++r)
        {
            if(a[l] < a[l+1])
                f[l][r][0] = (f[l][r][0] + f[l+1][r][0]) % mod;
            if(a[l] < a[r])
                f[l][r][0] = (f[l][r][0] + f[l+1][r][1]) % mod;
            if(a[r] > a[r-1])
                f[l][r][1] = (f[l][r][1] + f[l][r-1][1]) % mod;
            if(a[r] > a[l])
                f[l][r][1] = (f[l][r][1] + f[l][r-1][0]) % mod;
        }
    }
    printf("%d",(f[1][n][0] + f[1][n][1]) % mod);
    return 0;
}