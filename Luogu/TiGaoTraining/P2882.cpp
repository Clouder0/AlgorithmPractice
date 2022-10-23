#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 5e3 + 100;
int n,res = 1 << 30,tarK;
int a[maxn];
int tag[maxn];
char s[10];
int main()
{
    scanf("%d",&n);
    for(int i = 1;i<=n;++i)
    {
        scanf("%s",s+1);
        a[i] = (s[1] == 'B');
    }
    int ans,status;
    for(int k = 1;k<=n;++k)
    {
        ans = 0;
        status = 0;
        memset(tag,0,sizeof(tag));
        for(int i = 1;i<=n-k+1;++i)
        {
            if(tag[i])
                status ^= 1;
            if((status && !a[i]) || (!status && a[i]))
            {
                    status ^= 1;
                    tag[i+k] ^= 1;
                    ++ans;
            }
        }
        for(int i = n - k + 2;i<=n;++i)
        {
            if(tag[i])
                status ^= 1;
            if((status && !a[i]) || (!status && a[i]))
                goto end;
        }
        if(ans < res)
            res = ans,tarK = k;
        end:;
    }
    printf("%d %d",tarK,res);
    return 0;
}