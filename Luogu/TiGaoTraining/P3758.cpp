#include <cstdio>
#include <cstring>
const int maxn = 40;
const int mod = 2017;
struct matrix
{
    int n,m,a[maxn][maxn];
    matrix() { memset(a,0,sizeof(a)); }
    matrix(int n,int m) 
    {
        this->n = n,this->m = m;
        memset(a,0,sizeof(a));
    }
    matrix operator*(const matrix b)
    {
        matrix c(n, b.m);
        for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) for (int k = 1; k <= b.m; ++k) 
            c.a[i][k] = (c.a[i][k] + a[i][j] * b.a[j][k]) % mod;
        return c;
    }
};
int n,m,a[maxn][maxn],t;
int main()
{
    scanf("%d %d",&n,&m);
    for (int i = 1, x, y; i <= m; ++i) scanf("%d %d", &x, &y), a[x][y] = a[y][x] = 1;
    for (int i = 1; i <= n; ++i) a[i][i] = 1;
    matrix A(1,n + 1);
    A.a[1][1] = 1;
    matrix S(n + 1,n + 1);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) S.a[i][j] = a[i][j];
    for (int i = 1; i <= n + 1; ++i) S.a[i][n + 1] = 1;
    scanf("%d",&t);
    matrix B(n + 1,n + 1);
    for (int i = 1; i <= n + 1; ++i) B.a[i][i] = 1;
    ++t;
    while(t)
    {
        if(t & 1) B = B * S;
        S = S * S;
        t >>= 1;
    }
    A = A * B;
    printf("%d\n",A.a[1][n + 1]);
    return 0;
}