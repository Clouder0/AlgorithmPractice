#include <cstdio>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c; r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
inline int min(const int &a,const int &b){return a<b?a:b;}
inline int min(const int &a,const int &b,const int &c){return min(min(a,b),c);}
int a,b,c,d,e,f;
int main()
{
    read(a);
    read(c);
    read(d);
    read(b);
    read(e);
    read(f);
    int can = min(c,d);
    if(e >= f)
    {
        if(b <= a)
        {
            printf("%d",e * b);
            return 0;
        }
        else
        {
            int ans = e * a;
            b -= a;
            can = min(b,can);
            ans += can * f;
            printf("%d",ans);
            return 0;
        }
    }
    else
    {
        if(can >= b)
        {
            printf("%d",b * f);
            return 0;
        }
        else
        {
            int ans = can * f;
            b -= can;
            can = min(a,b);
            ans += can * e;
            printf("%d",ans);
            return 0;
        }
    }
    return 0;
}