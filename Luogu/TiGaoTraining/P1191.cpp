#include <cstdio>
using namespace std;
template<typename T>
inline T min(const T &a,const T &b){return a<b?a:b;}
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
int n;
int all[160][160];
int up[160][160];
char s[160];
int main()
{
    read(n);
    for(int i = 1;i<=n;++i)
    {
        scanf("%s",s+1);
        for(int j = 1;j<=n;++j)
            all[i][j] = (s[j]=='W'?1:0);
    }
    for(int i = 1;i<=n;++i)
        for(int j = 1;j<=n;++j)
            if(all[i][j])
                up[i][j] = up[i-1][j] + 1;
    int ans = 0;
    for(int i = n;i;--i)
        for(int j = 1;j<=n;++j)
        {
            int h = up[i][j];
            for(int k = 1;j+k-1<=n;++k)
            {
                h = min(h,up[i][j+k-1]);
                ans += h;
            }
        }
    printf("%d",ans);
    return 0;
}