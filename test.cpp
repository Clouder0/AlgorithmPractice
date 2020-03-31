#include <cstdio>
using namespace std;
inline char nc()
{
    static char buf[100000],*p1,*p2;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1 == p2)?EOF:*p1++;
}
template<typename T>
inline T read(T &r)
{
    static char c;r=0;
    for(c=nc();c>'9'||c<'0';c=nc());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=nc());
    return r;
}
int main()
{
    return 0;
}