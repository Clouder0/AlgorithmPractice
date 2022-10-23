#include <cstdio>
#include <algorithm>
using namespace std;
int T,a[3];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        int ans = 1;
        scanf("%d %d %d",a,a + 1,a + 2);
        do
        {
            ans = max(ans, a[0] - a[1] - a[2] + 1);
        } while (next_permutation(a, a + 3));
        printf("%d\n",ans);
    }
    return 0;
}