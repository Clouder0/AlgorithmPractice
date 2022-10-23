#include <cstdio>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
int t,n;
int main()
{
    read(t);
    while(t--)
    {
        read(n);
        if(n % 2)
        {
            putchar('7');
            for(int i = 1;i<n/2;++i)
                putchar('1');
            putchar('\n');
        }
        else
        {
            for(int i = 1;i<=n/2;++i)
                putchar('1');
            putchar('\n');
        }
    }
    return 0;
}