#include <cstdio>
using namespace std;
const int maxn = 1e6 + 10;
int n,k;
int origin[maxn];
int q[maxn],qh = 1,qt = 0;
int main() 
{
    scanf("%d%d",&n,&k);
    for(int i = 1;i<=n;++i)
        scanf("%d",origin+i);
    for(int i = 1;i<=n;++i)
    {
        while(qt >= qh && origin[i] <= origin[q[qt]])
            --qt;
        q[++qt] = i;
        while(q[qt] - q[qh] + 1 > k)
            ++qh;
        if(i >= k)
            printf("%d ",origin[q[qh]]);
    }
    qh = 1,qt = 0;
    putchar('\n');
    for(int i = 1;i<=n;++i)
    {
        while(qt >= qh && origin[i] >= origin[q[qt]])
            --qt;
        q[++qt] = i;
        while(q[qt] - q[qh] + 1 > k)
            ++qh;
        if(i >= k)
            printf("%d ",origin[q[qh]]);
    }
    return 0;
}