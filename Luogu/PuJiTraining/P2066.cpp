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
const int maxn = 20;
int n,m;
long long a[maxn][maxn];
long long f[maxn][maxn];
int g[maxn][maxn];
void output(int i,int j)
{
    if(i == 0) return;
    output(i-1,j - g[i][j]);
    printf("%d %d\n",i,g[i][j]);
}
int main()
{
    read(n),read(m);
    for(int i = 1;i<=n;++i)
        for(int j = 1;j<=m;++j)
            read(a[i][j]);
    for(int i = 1;i<=n;++i)
        for(int j = 0;j<=m;++j)
            for(int k = 0;j+k<=m;++k)
                if(f[i][j+k] < f[i-1][j] + a[i][k])
                {
                    f[i][j+k] = f[i-1][j] + a[i][k];
                    g[i][j+k] = k;
                }
    printf("%lld\n",f[n][m]);
    output(n,m);
    return 0;
}