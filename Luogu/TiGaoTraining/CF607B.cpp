#include <cstdio>
#include <cstring>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 510;
int n;
int f[maxn][maxn];
int a[maxn];
int main()
{
    memset(f,0x3f,sizeof(f));
    read(n);
    for(int i = 1;i<=n;++i)
        read(a[i]);
    for(int i = 1;i<=n;++i)
        f[i][i] = 1;
    for(int i = 1;i<n;++i)
        if(a[i] == a[i+1])
            f[i][i+1] = 1;
        else
            f[i][i+1] = 2;
    for(int len = 3;len<=n;++len)
    {
        for(int l = 1,r = l + len - 1;r<=n;++l,++r)
        {
            if(a[l] == a[r])
                f[l][r] = f[l+1][r-1];
            for (int k = l; k < r; ++k)
                if (f[l][r] > f[l][k] + f[k + 1][r])
                    f[l][r] = f[l][k] + f[k + 1][r];
        }
    }
    printf("%d",f[1][n]);
    return 0;
}