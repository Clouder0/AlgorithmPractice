#include <cstdio>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 250;
int n;
int a[maxn];
int f[maxn][maxn];
int ans;
int main()
{
    read(n);
    for(int i = 1;i<=n;++i)
        read(a[i]);
    for(int i = 1;i<=n;++i)
        f[i][i] = a[i];
    for(int len = 2;len<=n;++len)
    {
        for(int l = 1,r = l + len - 1;r<=n;++l,++r)
        {
            for(int k = l;k<r;++k)
                if(f[l][k] == f[k+1][r] && f[l][k] + 1 > f[l][r])
                    f[l][r] = f[l][k] + 1,ans = ans>f[l][r]?ans:f[l][r];
        }
    }
    printf("%d",ans);
    return 0;
}