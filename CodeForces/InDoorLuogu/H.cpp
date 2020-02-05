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
int n,T;
struct fuck
{
    int w,v;
    bool operator<(const fuck &b)    const
    {
        return v*b.w > b.v*w;
    }
}a[1100];
int main()
{
    read(n);
    read(T);
    for(int i = 1;i<=n;++i)
        read(a[i].w),read(a[i].v);
    sort(a+1,a+1+n);
    double ans = 0;
    for(int i = 1;i<=n;++i)
        if(T <= a[i].w)
        {
            ans += T * (double)a[i].v / a[i].w;
            break;
        }
        else
        {
            ans += a[i].v;
            T -= a[i].w;
        }
    printf("%.2lf",ans);
    return 0;
}