#include <cstdio>
#include <algorithm>
#include <set>
#include <ctype.h>
using namespace std;
#define DEBUG
const int bufSize = 1e6;
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
int T,n,k;
int a[310][310],R[310],C[310];
int main()
{
    read(T);
    while(T--)
    {
        read(n),read(k);
        for(int i = 1;i<=n;++i) for(int j = 1;j<=n;++j) a[i][j] = 0;
        for(int i = 1;i<=n;++i) R[i] = C[i] = 0;
        for(int p = 0;k;++p)
        {
            for(int i = 1 + p;k && i<=n;++i) a[i - p][i] = 1,--k;
            for(int i = 1;k && i <= p;++i)  a[n - p + i][i] = 1,--k;
        }
        int maxa = 0,maxb = 0,mina = 1<<30,minb = 1<<30;
        for(int i = 1;i<=n;++i) for(int j = 1;j<=n;++j) R[i] += a[i][j],C[i] += a[i][j];
        for(int i = 1;i<=n;++i) maxa = max(maxa,R[i]),mina = min(mina,R[i]),maxb = max(maxb,C[i]),minb = min(minb,C[i]);
        printf("%d\n",(maxa - mina) * (maxa - mina) + (maxb - minb) * (maxb - minb));
        for(int i = 1;i<=n;putchar('\n'),++i) for(int j = 1;j<=n;++j) printf("%d",a[i][j]);
    }
    return 0;
}