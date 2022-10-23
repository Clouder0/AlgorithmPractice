#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1e5 + 100;
int n,a[maxn],b[maxn];
int main()
{
    scanf("%d",&n);
    for (int i = 1; i <= n; ++i) scanf("%d",a + i);
    sort(a + 1,a + 1 + n);
    int p1 = 1,p2 = n / 2 + 1;
    for (int i = 1; i <= n; ++i) 
    {
        if(i & 1) b[i] = a[p2++];
        else b[i] = a[p1++];
    }
    int ans = 0;
    for (int i = 2; i < n; ++i) if(b[i] < b[i+1] && b[i] < b[i-1]) ++ans;
    printf("%d\n",ans);
    for (int i = 1; i <= n; ++i) printf("%d ",b[i]);
    return 0;
}