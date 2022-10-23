#include <cstdio>
#include <bitset>
#include <algorithm>
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
const int maxn = 160;
const long long inf = 1ll<<58;
int n,m,ans = inf;
struct matrix
{
    std::bitset<maxn> a[maxn];
    matrix(){for(int i = 1;i<=n;++i)a[i].reset();}
    matrix operator*(const matrix &b)
    {
        matrix c;
        for(int i = 1;i<=n;++i)
            for(int j = 1;j<=n;++j)
                if(a[i][j]) c.a[i] |= b.a[j];
        return c;
    }
};
struct Edge
{
    int u,v,d;
    bool operator<(const Edge &b){return this->d < b.d;}
}E[maxn];
int dis[maxn][maxn];
signed main()
{
    read(n),read(m);
    for(int i = 1;i<=m;++i) read(E[i].u),read(E[i].v),read(E[i].d);
    std::sort(E + 1,E + 1 + m);
    matrix A;
    for(int i = 1;i<=n;++i) A.a[i][i] = 1;
    for(int i = 1;i<=m;++i)
    {
        int t = E[i].d - E[i-1].d;
        matrix em;
        for(int j = 1;j<i;++j) em.a[E[j].u][E[j].v] = 1;
        while(t)
        {
            if(t & 1) A = A * em;
            em = em * em;
            t >>= 1;
        }
        for(int a = 1;a<=n;++a)
            for(int b = 1;b<=n;++b)
                dis[a][b] = ((a==b)?(0):inf);
        for(int j = 1;j<=i;++j) dis[E[j].u][E[j].v] = 1;
        for(int k = 1;k<=n;++k) 
            for(int a = 1;a<=n;++a) 
                for(int b = 1;b<=n;++b) 
                    dis[a][b] = min(dis[a][b],dis[a][k] + dis[k][b]);
        for(int j = 1;j<=n;++j) if(A.a[1][j] && E[i].d + dis[j][n] < ans) ans = E[i].d + dis[j][n];
    }
    if(ans == inf) puts("Impossible");
    else printf("%lld",ans);
    return 0;
}