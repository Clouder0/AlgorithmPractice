#include <cstdio>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
int T,n,x;
char all[1000000];
int sum[1000000];
int main()
{
    read(T);
    while(T--)
    {
        read(n);
        read(x);
        scanf("%s",all+1);
        for(int i = 1;i<=n;++i)
            sum[i] = sum[i-1] + (all[i] == '0'?1:-1);
        int ans = 0;
        if(sum[n] == 0)
        {
            for(int i = 1;i<=n;++i)
                if(sum[i] == x)
                {
                    printf("-1\n");
                    goto end;
                }
            printf("0\n");
            goto end;
        }
        for(int i = 0;i<n;++i)
            if((x - sum[i]) / sum[n] >= 0 && (x - sum[i]) % sum[n] == 0)
                ++ans;
        printf("%d\n",ans);
        end:;
    }
    return 0;
}