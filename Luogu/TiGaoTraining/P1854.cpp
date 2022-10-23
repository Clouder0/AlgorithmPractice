#include <cstdio>
template<typename T>
void read(T &r)
{
    static char c;static int flag;flag = 1,r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar()) if(c == '-') flag = -1;
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
    r *= flag;
}
const int maxn = 110;
int n,m;
int a[maxn][maxn];
int f[maxn][maxn],g[maxn][maxn];
void output(int i,int j)
{
    if(i == 0) return;
    output(i-1,g[i][j]);
    printf("%d ",j);
}
int main()
{
    read(n),read(m);
    for(int i = 1;i<=n;++i)
        for(int j = 1;j<=m;++j)
            read(a[i][j]),f[i][j] = 1<<31;
    for(int i = 1;i<=m;++i)
        f[1][i] = a[1][i];
    for(int i = 2;i<=n;++i)
        for(int j = i - 1;j<=m;++j)
        {
            for(int k = j + 1;k<=m;++k)
                if(f[i-1][j] + a[i][k] > f[i][k])
                    f[i][k] = f[i-1][j] + a[i][k],g[i][k] = j;
        }
    int ansp = 0;
    for(int i = 1;i<=m;++i)
        if(f[n][ansp] < f[n][i])
            ansp = i;
    printf("%d\n",f[n][ansp]);
    output(n,ansp);
    return 0;
}