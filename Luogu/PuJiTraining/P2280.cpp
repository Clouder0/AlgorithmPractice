#include <cstdio>
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 5000 + 100;
int sum[maxn][maxn];
int n,m,maxx,maxy;
int main()
{
    read(n),read(m);
    for(int i = 1;i<=n;++i)
    {
        int x,y,v;
        read(x),read(y),read(v);
        ++x,++y;
        maxx = maxx>x?maxx:x;
        maxy = maxy>y?maxy:y;
        sum[x][y] += v;
    }
    for(int i = 1;i<=maxx;++i)
        for(int j = 1;j<=maxy;++j)
            sum[i][j] += sum[i][j-1];
    for(int i = 1;i<=maxx;++i)
        for(int j = 1;j<=maxy;++j)
            sum[i][j] += sum[i-1][j];
    int ans = 0;
    for(int i = 1;i<=maxx;++i)
        for(int j = 1;j<=maxy;++j)
        {
            int t;
            if(i < m && j < m) t = sum[i][j];
            else if(i < m) t = sum[i][j] - sum[i][j-m];
            else if(j < m) t = sum[i][j] - sum[i-m][j];
            else t = sum[i][j] - sum[i-m][j] - sum[i][j-m] + sum[i-m][j-m];
            ans = ans > t ? ans : t;
        }
    printf("%d",ans);
    return 0;
}