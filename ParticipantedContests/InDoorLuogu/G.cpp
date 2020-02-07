#include <cstdio>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
int n,a,b,c;
int main()
{
    read(n);
    while(n--)
    {
        read(a);
        read(b);
        read(c);
        if(0.7 * b + 0.3 * c > 80.0 && b + c > 140)
            puts("Excellent");
        else
            puts("Not excellent");
    }
    return 0;
}