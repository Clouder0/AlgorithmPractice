#include <cstdio>
using namespace std;
int n;
int all[110];
int main()
{
    scanf("%d",&n);
    int sum = 0;
    for(int i = 1;i<=n;++i)
        scanf("%d",all+i),sum += all[i];
    sum /= n;
    for(int i = 1;i<=n;++i)
        all[i] -= sum;
    sum = 0;
    for(int i = 1;i<=n;++i)
    {
        if(all[i] == 0) continue;
        all[i+1] += all[i],++sum;
        all[i] = 0;
    }
    printf("%d",sum);
    return 0;
}