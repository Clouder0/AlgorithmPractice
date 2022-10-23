#include <cstdio>
using namespace std;
template<typename T>
inline void read(T &r)
{
    static char c;static int flag;flag = 1,r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar()) if(c == '-') flag = -1;
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
    r *= flag;
}
const int maxn = 1e6 + 10;
int n,a,b,c;
long long s[maxn];
long long f[maxn];
int q[maxn],head = 1,tail;
long long gx(int x)
{
    return s[x];
}
long long gy(int x)
{
    return f[x] + a * s[x] * s[x] - b * s[x];
}
int cmp2(int x1,int x2,int x3)
{
    return (gy(x2) - gy(x1)) * (gx(x3) - gx(x2)) <= (gy(x3) - gy(x2)) * (gx(x2) - gx(x1));
}
int cmp1(int x1,int x2,long long k)
{
    return gy(x2) - gy(x1) > k * (gx(x2) - gx(x1));
}
int main()
{
    read(n);
    read(a);
    read(b);
    read(c);
    for(int i = 1;i<=n;++i)
        read(s[i]),s[i] += s[i-1];
    q[++tail] = 0;
    for(int i = 1;i<=n;++i)
    {
        while(tail > head && cmp1(q[head],q[head+1],2 * a * s[i])) ++head;
        f[i] = gy(q[head]) - 2 * a * s[i] * gx(q[head]) + a * s[i] * s[i] + b * s[i] + c;
        while(tail > head && cmp2(q[tail-1],q[tail],i)) --tail;
        q[++tail] = i;
    }
    printf("%lld",f[n]);
    return 0;
}