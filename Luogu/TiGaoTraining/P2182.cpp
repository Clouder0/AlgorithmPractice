#include <stdio.h>
#include <memory.h>
const int maxn = 110;
const int mod = 1000000007;
int n,k,m;
int dif;
char s1[maxn],s2[maxn];
long long f[2][maxn];//f[i] i sames.
long long c[maxn][maxn];
int main()
{   
    scanf("%d %d %d",&n,&k,&m);
    c[1][1] = 1;
    for(int i = 2;i<=n+1;++i)
        for(int j = 1;j<=i;++j)
            c[i][j] = (c[i-1][j] + c[i-1][j-1]) % mod;
    scanf("%s",s1+1);
    scanf("%s",s2+1);
    for(int i = 1;i<=n;++i) dif += (s1[i] != s2[i]);
    int now = 0,last = 1;
    f[last][n - dif] = 1;
    while(k--)
    {
        memset(f[now],0,sizeof(f[now]));
        for(int i = 0;i<=n;++i)// origin same
            for(int j = 0;j<=m;++j)//choose j same->diff, n - j diff->same
            {
                int num = i - j + m - j;
                if(num > n || num < 0) continue;
                f[now][num] += ((f[last][i] * c[i+1][j+1]) % mod * c[n-i+1][m-j+1]) % mod;
                if(f[now][num] > mod) f[now][num] %= mod;
            }
        now ^= 1,last ^= 1;
    }
    printf("%lld",f[last][n] % mod);
    return 0;
}