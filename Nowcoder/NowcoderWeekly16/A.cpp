#include <cstdio>
#include <algorithm>
#include <ctype.h>
#define DEBUG
const int bufSize = 1e6;
#define int long long
int n,m,T;
signed main()
{
    scanf("%lld %lld %lld",&m,&n,&T);
    int size =  n / m;
    int final = n - size * (m - 1);
    while(T--)
    {
        int x;
        scanf("%lld",&x);
        if(x <= m) printf("%lld\n",size);
//        else if(x == m) printf("%lld\n",final);
        else printf("0\n");
    }
    return 0;
}