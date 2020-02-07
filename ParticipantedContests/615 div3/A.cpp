#include <cstdio>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
int t,a,b,c,n;
int main()
{
    read(t);
    while(t--)
    {
        read(a);
        read(b);
        read(c);
        read(n);
        int maxx = 0;
        if(a > maxx)
            maxx = a;
        if(b > maxx)
            maxx = b;
        if(c > maxx)
            maxx = c;
        int ba = maxx - a,bb = maxx - b,bc = maxx - c;
        int bs = ba + bb + bc;
        if(bs > n)
        {
            printf("NO\n");
            continue;
        }
        n -= bs;
        if(n % 3)
        {
            puts("NO\n");
            continue;
        }
        puts("YES\n");
    }
    return 0;
}
