#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 2e5 + 100;
int T,n,a[maxn],f[maxn][2];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for (int i = 1; i <= n; ++i) scanf("%d",a+i);
        for (int i = 1; i <= n; ++i) f[i][0] = f[i][1] = 1 << 30;
        f[1][0] = a[1];
        f[2][0] = a[1] + a[2], f[2][1] = a[1];
        for (int i = 3; i <= n; ++i)
        {
            //I killed 1/2 monsters
            f[i][1] = min(f[i-1][0],f[i-2][0]);
            //friend killed 1/2 monsters
            f[i][0] = min(f[i - 1][1] + a[i], f[i - 2][1] + a[i - 1] + a[i]);
        }
        printf("%d\n",min(f[n][0],f[n][1]));
    }
    return 0;
}