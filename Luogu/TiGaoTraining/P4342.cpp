#include <cstdio>
#include <cstring>
template<typename T>
inline T max(const T &a,const T &b){return a>b?a:b;}
template<typename T>
inline T min(const T &a,const T &b){return a<b?a:b;}
template<typename T>
inline void read(T &r)
{
    static char c;
    static int flag;
    r = 0,flag = 1;
    for(c = getchar();c>'9'||c<'0';c=getchar())
        if(c == '-') flag = -1;
    for(;c<='9'&&c>='0';r=r*10+c-48,c=getchar());
    r *= flag;
}
const int maxn = 60;
int n;
int opt[maxn*2],a[maxn*2];
int f[maxn*2][maxn*2],g[maxn*2][maxn*2];
int main()
{
    read(n);
    char temp[3];
    for(int i = 1;i<=n;++i)
    {
        scanf("%s",temp);
        opt[i] = (temp[0] == 'x');
        read(a[i]);
        a[i+n] = a[i],opt[i+n] = opt[i];
    }
    memset(f,~0x3f,sizeof(f));
    memset(g,0x3f,sizeof(g));
    for(int i = 1;i<=2*n;++i)
        f[i][i] = g[i][i] = a[i];
    for(int len = 2;len<=n;++len)
    {
        for(int l = 1,r = l + len - 1;r<=2*n;++l,++r)
        {
            for(int k = l;k<r;++k)
            {
                if(opt[k+1] == 0)
                {
                    f[l][r] = max(f[l][r],f[l][k] + f[k+1][r]);
                    g[l][r] = min(g[l][r],g[l][k] + g[k+1][r]);
                }
                else
                {
                    f[l][r] = max(f[l][r],max(f[l][k] * f[k+1][r],max(g[l][k] * f[k+1][r],max(g[l][k] * g[k+1][r],f[l][k] * g[k+1][r]))));
                    g[l][r] = min(g[l][r],min(f[l][k] * f[k+1][r],min(g[l][k] * f[k+1][r],min(g[l][k] * g[k+1][r],f[l][k] * g[k+1][r]))));
                }
            }
        }
    }
    int ans = 1<<31,point = 0;
    for(int i = 1;i<=n;++i)
        if(f[i][i+n-1] > ans)
            ans = f[i][i+n-1];
    printf("%d\n",ans);
    for(int i = 1;i<=n;++i)
        if(f[i][i+n-1] == ans)
            printf("%d ",i);
    return 0;
}