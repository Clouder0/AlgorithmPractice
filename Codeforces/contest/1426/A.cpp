#include <cstdio>
#include <algorithm>
using namespace std;
int T,n,x;
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&x);
        if(n <= 2) puts("1");
        else printf("%d\n",(n - 2 + x - 1) / x + 1);
    }
    return 0;
}