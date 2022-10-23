#include <cstdio>
template<typename T>
inline T max(const T &a,const T &b){return a>b?a:b;}
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 110;
int a[maxn][maxn],f[maxn][maxn];
int n,m;
int main()
{
    read(n),read(m);
    for(int i = 1;i<=n;++i) for(int j = 1;j<=m;++j) read(a[i][j]);
    for(int i = 0;i <= n + 1;++i) for(int j = 0;j <= m + 1;++j) f[i][j] = -100000000;
    f[1][1] = a[1][1];
    for(int j = 2;j<=m;++j) for(int i = 1;i<=n;++i) f[i][j] = max(f[i-1][j-1],max(f[i][j-1],f[i+1][j-1])) + a[i][j];
    printf("%d",f[n][m]);
    return 0;
}