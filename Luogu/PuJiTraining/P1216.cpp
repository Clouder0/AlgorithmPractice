#include <cstdio>
const int maxn = 1100;
int n;
int a[maxn][maxn], f[maxn][maxn];
inline int max(const int &a,const int &b){return a > b ? a : b;}
int main(){
    scanf("%d",&n);
    for(int i = 1;i<=n;++i)
    {
        for(int j = 1;j<=i;++j)
        {
          scanf("%d",a[i] + j);
        }
    }
    for(int i = 1;i<=n;++i)
        for(int j = 1;j<=i;++j) f[i][j] = max(f[i-1][j-1],f[i-1][j]) + a[i][j];
    int maxx = 0;
    for(int i = 1;i<=n;++i) maxx = max(maxx,f[n][i]);
    printf("%d\n",maxx);
    return 0;
}