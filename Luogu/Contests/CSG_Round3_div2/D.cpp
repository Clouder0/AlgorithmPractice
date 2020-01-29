#include <cstdio>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
int n,T;
int p[510],a[510];
int fr[510][510];
int main()
{
    read(n);
    read(T);
    for(int i = 1;i<=n;++i)
    {
        read(p[i]);
        read(a[i]);
        for(int p = 1;p<=a[i];++p)
            read(fr[i][p]);
    }
    for(int i = 1;i<=n;++i)
    {

    }
    return 0;
}