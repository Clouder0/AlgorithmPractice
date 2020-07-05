#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 2100;
int n,p;
int a[maxn],L[maxn];
int A[maxn],ans[maxn],tot,out[maxn*maxn],cnt;
int main()
{
    scanf("%d %d",&n,&p);
    A[0] = 1;
    for(int i = 1;i<=n;++i) A[i] = (i * A[i-1]) % p;
    for(int i = 1;i<=n;++i) scanf("%d",a + i);
    std::sort(a + 1,a + 1 + n);
    L[0] = 1;
    int start = a[1];
    for(int i = 2;i<=n;++i) if(a[i] - a[i-1] > 1) start += a[i] - a[i-1] - 1;
    for(int i = 1;i<=n;++i) L[i] = (a[i-1] == a[i] ? L[i-1] : i);
    int sp = 1;
    while(a[sp] < start) ++sp;
    --sp;
    for(int i = sp;i<=n;++i) if(A[i - L[i]] * A[i] % p) ans[++tot] = i;
    for(int i = 1;i<=tot;++i)
    {
        //printf("ans:%d\n",i);
        for(int j = max(a[ans[i]],a[ans[i] + 1] - ans[i]);j<a[ans[i] + 1];++j) out[++cnt] = j;
    }
    printf("%d\n",cnt);
    for(int i = 1;i<=cnt;++i) printf("%d ",out[i]);
    return 0;
}