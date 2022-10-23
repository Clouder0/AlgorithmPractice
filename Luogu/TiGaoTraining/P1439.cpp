#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 2e5 + 100;
int n, a[maxn], b[maxn], pos[maxn], cur[maxn], top;
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i), pos[a[i]] = i;
    for (int i = 1; i <= n; ++i) scanf("%d", b + i), b[i] = pos[b[i]];
    for (int i = 1; i <= n; ++i) 
    {
        int p = lower_bound(cur + 1,cur + 1 + top, b[i]) - cur;
        cur[p] = b[i];
        if(p > top) top = p;
    }
    printf("%d\n", top);
    return 0;
}