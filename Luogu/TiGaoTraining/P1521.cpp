#include <cstdio>
const int mod = 10000;
int n,m;
int f[2][11000];
int main()
{
    scanf("%d %d",&n,&m);
    int now = 0,last = 1;
    f[last][0] = 1,f[last][1] = 1;
    for(int i = 3;i<=n;++i)
    {
        f[now][0] = 1;
        for(int j = 1;j<=m;++j)
        {
            f[now][j] = f[now][j-1] + f[last][j];
            if(j - i >= 0) f[now][j] -= f[last][j-i];
            if(f[now][j] >= mod) f[now][j] %= mod;
            else if(f[now][j] < 0) f[now][j] = (f[now][j] + mod) % mod;
        }
        now ^= 1,last ^= 1;
    }
    printf("%d",f[last][m]);
    return 0;
}