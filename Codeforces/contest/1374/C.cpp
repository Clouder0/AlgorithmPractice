#include <cstdio>
const int maxn = 60;
int T,n;
char s[maxn];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %s",&n,s+1);
        int sum = 0;
        for(int i = 1;i<=n;++i)
        {
            sum += (s[i] == '(' ? 1 : -1);
            if(sum < 0) sum = 0;
        }
        printf("%d\n",sum);
    }
    return 0;
}