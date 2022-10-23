#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1100;
int T,n,a[maxn],k;
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&k);
        int minn = 1<<30,mini = 1;
        for (int i = 1; i <= n; ++i) scanf("%d",a + i),minn = min(minn,a[i]);
        for (int i = 1; i <= n; ++i) if(minn == a[i]) mini = i;
        int ans = 0;
        for (int i = 1; i <= n; ++i) if(i != mini) ans += max(0,(k - a[i]) / minn);
        printf("%d\n",ans);
    }
    return 0;
}