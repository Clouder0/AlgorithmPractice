#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;
const int maxn = 2e5 + 100;
int n,a[maxn];
long long sum[maxn];
set<long long> s;
int main()
{
    scanf("%d",&n);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    for (int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + a[i];
    int p = 0,ans = 0;
    s.insert(0);
    for (int i = 1; i <= n; ++i) 
    {
        set<long long>::iterator it = s.find(sum[i]);
        if (it != s.end()) ++ans, s.clear(), s.insert(sum[i - 1]);
        s.insert(sum[i]);
    }
    printf("%d\n",ans);
    return 0;
}