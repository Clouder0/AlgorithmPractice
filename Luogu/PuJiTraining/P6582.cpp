#include <cstdio>
#include <cstring>
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 1100;
const int mod = 998244353;
int n,m,k;
char s[maxn];
int a[maxn][maxn],A[maxn][maxn];
long long ans = 1;
int main()
{
    read(n),read(m),read(k);
    for(int i = 1;i<=n;++i)
    {
        scanf("%s",s+1);
        for(int j = 1;j<=m;++j)
        {
            a[i][j] = (s[j] == 'O')?1:0;
            A[i][j] = a[i-1][j] + a[i][j-1];
            if(a[i-1][j] + a[i+1][j] + a[i][j-1] + a[i][j+1] >= 3 || (a[i][j-1] + a[i-1][j] + a[i-1][j-1]) == 3)
            {
                puts("0");
                return 0;
            }
        }
    }
    for(int i = 1;i<=n;++i)
        for(int j = 1;j<=m;++j)
            if(a[i][j])
            {
                ans = ans * (k - A[i][j]);
                if(ans > mod)
                    ans %= mod;
            }
    printf("%lld",ans);
    return 0;
}