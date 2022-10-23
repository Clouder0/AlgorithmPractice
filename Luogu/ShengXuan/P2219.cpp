#include <cstdio>
#include <cstring>
template<typename T>
inline T max(const T &a,const T &b){return a>b?a:b;}
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 1100;
int n,m,A,B,C,D;
int a[maxn][maxn];
int flower[maxn][maxn];
int green[maxn][maxn];
int f[maxn][maxn];
int g[maxn][maxn];
int q[maxn],head,tail;
int main()
{
    read(n),read(m),read(A),read(B),read(C),read(D);
    for(int i = 1;i<=n;++i) for(int j = 1;j<=m;++j) read(a[i][j]),a[i][j] += a[i][j-1];
    for(int i = 1;i<=n;++i) for(int j = 1;j<=m;++j) a[i][j] += a[i-1][j];
    for(int i = C;i<=n;++i) for(int j = D;j<=m;++j) flower[i][j] = a[i][j] - a[i-C][j] - a[i][j-D] + a[i-C][j-D];
    for(int i = A;i<=n;++i) for(int j = B;j<=m;++j) green[i][j] = a[i][j] - a[i-A][j] - a[i][j-B] + a[i-A][j-B];
    memset(f,0x3f,sizeof(f));
    memset(g,0x3f,sizeof(g));
    for(int i = 1;i<=n;++i)
    {
        head = 1,tail = 0;
        int p = D;
        for(int j = 1;j<=m;++j)
        {
            while(p > j - B + D && p < j)
            {
                while(tail >= head && flower[i][q[tail]] >= flower[i][p]) --tail;
                q[++tail] = p++;
            }
            while(tail >= head && q[head] <= j - B + D) ++head;
            if(tail >= head) f[i][j] = flower[i][q[head]];
        }
    }
    for(int j = 1;j<=m;++j)
    {
        head = 1,tail = 0;
        int p = C;
        for(int i = 1;i<=n;++i)
        {
            while(p > i - A + C && p < i)
            {
                while(tail >= head && f[q[tail]][j] >= f[p][j]) --tail;
                q[++tail] = p++;
            }
            while(tail >= head && q[head] <= i - A + C) ++head;
            if(tail >= head) g[i][j] = f[q[head]][j];
        }
    }
    int ans = 0;
    for(int i = A;i<=n;++i) for(int j = B;j<=m;++j) if(ans < green[i][j] - g[i][j]) ans = green[i][j] - g[i][j];
    printf("%d",ans);
    return 0;
}