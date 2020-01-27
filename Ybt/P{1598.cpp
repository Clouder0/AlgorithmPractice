#include <cstdio>
using namespace std;
int n,m;
int sum[200050];
int q[200050],qt,qh = 1;
int main()
{
    scanf("%d%d",&n,&m);
    int temp;
    for(int i = 1;i<=n;++i)
        scanf("%d",&temp),sum[i] = sum[i-1] + temp;
    long long ans = -(1ll<<50);
    sum[0] = 0;
    for(int i = 0;i<n;++i)
    {
        while(qt >= qh && sum[i] <= sum[q[qt]])
            --qt;
        q[++qt] = i;
        while(q[qt] - q[qh] + 1 > m)
            ++qh;
        if(sum[i+1] - sum[q[qh]] > ans)
            ans = sum[i+1] - sum[q[qh]];
    }
    printf("%lld",ans);
    return 0;
}