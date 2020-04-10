#include <cstdio>
#include <algorithm>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 1e5 + 10;
int T,n,x;
int a[maxn];
bool cmp(int a,int b)
{
    return a>b;
}
int main()
{
    read(T);
    while(T--)
    {
        read(n);
        read(x);
        for(int i = 1;i<=n;++i)
            read(a[i]);
        sort(a+1,a+1+n);
        long long now = 0;
        long long need = 0;
        int ans = 0;
        for(int i = n;i;--i)
        {
            now += a[i];
            need += x;
            if(now < need)
            {
                printf("%d\n",ans);
                goto end;
            }
            ++ans;
        }
        if(ans == n)
            printf("%d\n",ans);
        else if(ans == 0)
            puts("0");
        end:;
    }
    return 0;
}