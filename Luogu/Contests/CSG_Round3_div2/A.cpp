#include <cstdio>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
int n,a,b,t;
long long money,ans;
long long sealed[1000010];
int main()
{
    read(n);
    for(int i = 1;i<=n;++i)
    {
        money += sealed[i];
        read(t);
        read(a);
        if(t == 1)
            money += a;
        else if(t == 2)
        {
            if(money < a)
                ++ans;
            else
                money -= a;
        }
        else
        {
            read(b);
            money -= a;
            sealed[b] += a;
        }
    }
    printf("%d",ans);
    return 0;
}