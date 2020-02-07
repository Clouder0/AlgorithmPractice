#include <cstdio>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
int n,t;
int main()
{
    read(n);
    int ans = 1<<30;
    while(n--)
    {
        read(t);
        if(t < ans)
            ans = t;
    }
    printf("%d",ans);
    return 0;
}