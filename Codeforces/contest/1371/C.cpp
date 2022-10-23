#include <cstdio>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
using namespace std;
inline char nc()
{
    #ifdef DEBUG
    return getchar();
    #endif
    static char buf[bufSize],*p1 = buf,*p2 = buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,bufSize,stdin),p1==p2)?EOF:*p1++;
}
template<typename T>
inline T read(T &r)
{
    static char c;
    r=0;
    for(c = nc();!isdigit(c);) c = nc();
    for(;isdigit(c);c=nc()) r = r * 10 + c - 48;
    return r;
}
long long T,a,b,n,m;
int main()
{
    read(T);
    while(T--)
    {
        read(a),read(b),read(n),read(m);
        long long t = abs(a - b);
        if(n + m > a + b) goto NO;
//        if(a < t) goto NO;
        n -= t;
        if(a > b) a -= t;
        else b -= t;
        if(m > min(a,b)) goto NO;
        if(a > b) b -= m,m = 0;
        else a -= m,m = 0;
        if(n > a + b) goto NO;
        YES:
        puts("Yes");
        continue;
        NO:
        puts("No");
        continue;
    }
    return 0;
}