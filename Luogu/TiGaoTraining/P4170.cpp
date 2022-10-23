#include <cstdio>
#include <cstring>
using namespace std;
template<typename T>
inline T min(const T &a,const T &b){return a<b?a:b;}
const int maxn = 60;
int n;
char s[maxn];
int f[maxn][maxn];
int main()
{
    scanf("%s",s+1);
    n = strlen(s+1);
    memset(f,0x3f,sizeof(f));
    for(int i = 1;i<=n;++i)
        f[i][i] = 1;
    for(int len = 2;len<=n;++len)
    {
        for(int l = 1,r = l + len - 1;r<=n;++l,++r)
        {
            if(s[l] == s[r])
                f[l][r] = min(f[l+1][r],f[l][r-1]);
            else
                for(int k = l;k<r;++k)
                    f[l][r] = min(f[l][r],f[l][k] + f[k+1][r]);
        }
    }
    printf("%d",f[1][n]);
    return 0;
}