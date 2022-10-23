#include <cstdio>
#include <cstring>
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 110;
int n,m,q;
long long f[maxn];
struct matrix
{
    int n,m;
    long long a[maxn][maxn];
    matrix(){memset(a,0,sizeof(a));}
    matrix(const int &_n,const int &_m)
    {
        n = _n,m = _m;
        for(int i = 1;i<=n;++i) for(int j = 1;j<=m;++j) a[i][j] = 0;
    }
    matrix operator*(const matrix &b)
    {
        matrix c(this->n,b.m);
        for(int i = 1;i<=this->n;++i)
            for(int j = 1;j<=this->m;++j)
                for(int k = 1;k<=b.m;++k)
                    c.a[i][k] ^= this->a[i][j] * b.a[j][k];
        return c;
    }
};
matrix s[35],A;
signed main()
{
    read(n),read(m),read(q);
    for(int i = 1;i<=n;++i)
        read(f[i]);
    for(int i = 1;i<=m;++i)
    {
        int u,v;
        read(u),read(v);
        s[0].a[u][v] = s[0].a[v][u] = 1;
    }
    s[0].n = s[0].m = n;
    for(int t = 1;t<=31;++t)
    {
        s[t].n = s[t].m = n;
        s[t] = s[t-1] * s[t-1];
    }
    while(q--)
    {
        long long x,ans = 0;
        read(x);
        A.n = 1,A.m = n;
        for(int i = 1;i<=n;++i) A.a[1][i] = f[i];
        for(int p = 0;(1ll<<p)<=x;++p) if((x>>p) & 1) A = A * s[p];
        printf("%lld\n",A.a[1][1]);
    }
    return 0;
}