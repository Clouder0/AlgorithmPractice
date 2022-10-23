#include <cstdio>
#include <cstring>
#define int long long
template<typename T>
inline T min(const T &a,const T &b){return a<b?a:b;}
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 110,maxm = 2600,maxk = 1e6 + 100;
int n,m,k;
int a[maxn][maxn];
int U[maxm],V[maxm];
struct matrix
{
    int d[maxn][maxn];
    matrix(int x = (1ll<<60))
    {
        for(int i = 1;i<=n;++i) for(int j = 1;j<=n;++j) d[i][j] = x;
    }
    matrix operator*(const matrix &b)
    {
        matrix c;
        for(int i = 1;i<=n;++i)
            for(int j = 1;j<=n;++j)
                for(int k = 1;k<=n;++k)
                    c.d[i][k] = min(c.d[i][k],d[i][j] + b.d[j][k]);
        return c;
    }
};
int dis[maxn][maxn];
inline void floyd()
{
    std::memset(dis,0x3f,sizeof(dis));
    for(int i = 1;i<=n;++i) for(int j = 1;j<=n;++j) dis[i][j] = a[i][j];
    for(int i = 1;i<=n;++i) dis[i][i] = 0;
    for(int k = 1;k<=n;++k)
        for(int i = 1;i<=n;++i)
            for(int j = 1;j<=n;++j)
                if(dis[i][k] + dis[k][j] < dis[i][j])
                    dis[i][j] = dis[i][k] + dis[k][j];
}
signed main()
{
    memset(a,0x3f,sizeof(a));
    read(n),read(m),read(k);
    for(int i = 1;i<=m;++i)
    {
        int u,v,t;
        read(u),read(v),read(t);
        U[i] = u,V[i] = v;
        a[u][v] = t;
    }
    floyd();
    if(k == 0)
    {
        printf("%lld",dis[1][n]);
        return 0;
    }
    matrix A,ans;
    for(int i = 1;i<=m;++i)
    {
        int u = U[i],v = V[i],t = a[u][v];
        for(int j = 1;j<=n;++j)
            for(int k = 1;k<=n;++k)
                A.d[j][k] = min(A.d[j][k],min(dis[j][k],dis[j][u] + dis[v][k] - t));
    }
    for(int i = 1;i<=n;++i) for(int j = 1;j<=n;++j) ans.d[i][j] = dis[i][j];
    while(k)
    {
        if(k & 1) ans = ans * A;
        A = A * A;
        k>>=1;
    }
    printf("%lld",ans.d[1][n]);
    return 0;
}