#include <cstdio>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
int n;
int a[110];
int main()
{
    read(n);
    for(int i = 1;i<=n;++i)
        read(a[i]);
    for(int i = 1;i<=n;++i)
    {
        if(a[i] <= 1)
            goto no;
        for(int x = 2;x*x<=a[i];++x)
            if(a[i] % x == 0)
                goto no;
        printf("%d ",a[i]);
        no:;
    }
    return 0;
}