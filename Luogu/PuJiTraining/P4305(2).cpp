#include <cstdio>
#include <map>
using namespace std;
inline char nc()
{
    static char buf[10000000],*p1 = buf,*p2 = buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,10000000,stdin),p1==p2)?EOF:*p1++;
}
template<typename T>
inline T read(T &r)
{
    static char c;static int flag;flag = 1,r=0;
    for(c=nc();c>'9'||c<'0';c=nc()) if(c == '-') flag = -1;
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=nc());
    return r*=flag;
}
int n,T,temp;
map<int,bool> has;
int main()
{
    read(T);
    while(T--)
    {
        has.clear();
        read(n);
        for(int i = 1;i<=n;++i)
            if(!has[read(temp)])
            {
                has[temp] = true;
                printf("%d ",temp);
            }
        putchar('\n');
    }
    return 0;
}