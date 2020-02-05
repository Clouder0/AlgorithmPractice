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
int a[2100];
int main()
{
    read(T);
    while(T--)
    {
        read(n);
        int sum = 0,one = 0,two = 0;
        for(int i = 1;i<=n;++i)
            read(a[i]),sum += a[i];
        for(int i = 1;i<=n;++i)
            if(a[i] % 2)
                one = 1;
            else
                two = 1;
        if(one && two)
            puts("YES");
        else if(two)
            puts("NO");
        else if(n % 2 == 0 && one && !two)
            puts("NO");
        else if(n % 2 == 1 && one)
            puts("YES");
    }
    return 0;
}