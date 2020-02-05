#include <cstdio>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
int n,t,maxx,minn;
int main()
{
    read(n);
    minn = 1<< 30;
    maxx = -1;
    while(n--)
    {
        read(t);
        if(maxx < t)
            maxx = t;
        if(minn > t)
            minn = t;
    }
    printf("%d",maxx-minn);
    return 0;
}