#include <cstdio>
using namespace std;
template<typename T>
inline void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 5e4 + 10;
int n,L;
int c[maxn];
long long cs[maxn];
long long f[maxn];
int head,tail;
int q[maxn];
inline long long a(int x)
{
    return cs[x] + x;
}
inline long long b(int x)
{
    return a(x) + L + 1;
}
inline long long gx(int x)
{
    return b(x);
}
inline long long gy(int x)
{
    return f[x] + b(x) * b(x);
}
int cmp1(int x1,int x2,long long k)
{
    return gy(x2) - gy(x1) < k * (gx(x2) - gx(x1));
}
int cmp2(int x1,int x2,int x3)
{
    return (gy(x2) - gy(x1)) * (gx(x3) - gx(x2)) >= (gy(x3) - gy(x2)) * (gx(x2) - gx(x1));
}
int main()
{
    read(n);
    read(L);
    for(int i = 1;i<=n;++i)
        read(c[i]),cs[i]  = cs[i-1] + c[i];
    head = 1,tail = 0;
    q[++tail] = 0;
    for(int i = 1;i<=n;++i)
    {
        while(tail > head && cmp1(q[head],q[head+1],((cs[i] + i) << 1))) ++head;
        f[i] = f[q[head]] + (cs[i] - cs[q[head]] + i - q[head] - L - 1) * (cs[i] - cs[q[head]] + i - q[head] - L - 1);
        while(tail > head && cmp2(q[tail-1],q[tail],i)) --tail;
        q[++tail] = i;
    }
    printf("%lld",f[n]);
    return 0;
}