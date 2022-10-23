#include <cstdio>
#include <algorithm>
template<typename T>
inline T min(const T &a,const T &b){return a<b?a:b;}
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 1100;
int T,n,m;
int a[maxn];
int main()
{
    read(T);
    while(T--)
    {
        read(n),read(m);
        int t = 0;
        double sum = 0;
        for(int i = 1;i<=n;++i)
        {
            int x;
            read(a[i]),read(x);
            t += x;
            sum += a[i];
        }
        t = min(m,t);
        std::sort(a + 1,a + 1 + n);
        for (int i = n; i >= n - t + 1; --i) sum -= a[i] * 1.0 / 2;
        printf("%.1f\n",sum);
    }
    return 0;
}