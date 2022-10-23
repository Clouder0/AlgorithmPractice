#include <cstdio>
using namespace std;
int all[1100];
int n,temp,cnt;
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &temp);
        if(all[temp] != 1)
            all[temp] = 1,++cnt;
    }
    printf("%d\n",cnt);
    for(int i = 0;i<=1000;++i)
        if(all[i])
            printf("%d ",i);
    return 0;
}