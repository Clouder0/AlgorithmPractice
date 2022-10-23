#include <cstdio>
#include <cstring>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;static int flag;flag = 1,r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar()) if(c == '-') flag = -1;;
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
    r *= flag;
}
const int maxn = 3e5 + 10;
int n,s;
long long t[maxn],c[maxn];
long long f[maxn];
int q[maxn],head,tail;
int cmp1(int x1,int x2,int x3)
{
    return (long long)(f[x2] - f[x1]) * (c[x3] - c[x2]) >= (long long)(f[x3] - f[x2]) * (c[x2] - c[x1]);
}
int cmp2(int x1,int x2,int k)
{
    return f[x2] - f[x1] <= (long long)k * (c[x2] - c[x1]);
}
int search(int l,int r,long long k)
{
    int mid,ans = 0;
    while(l <= r)
    {
        mid = l + r >> 1;
        if(f[q[mid+1]] - f[q[mid]] > k * (c[q[mid+1]] - c[q[mid]]))
            ans = mid,r = mid - 1;
        else
            l = mid + 1;
    }
    return q[ans];
}
int main()
{
    read(n);
    read(s);
    for(int i = 1;i<=n;++i)
        read(t[i]),read(c[i]),t[i] += t[i-1],c[i] += c[i-1];
    memset(f,0x3f,sizeof(f));
    f[0] = 0;
    head = 1;
    q[++tail] = 0;
    for(int i = 1;i<=n;++i)
    {
        int p = search(head,tail,t[i] + s);
        f[i] = f[p] + (long long)t[i] * c[i] + s * c[n] - c[p] * (t[i] + s);
        while(tail > head && cmp1(q[tail-1],q[tail],i)) --tail;
        q[++tail] = i;
    }
    printf("%lld",f[n]);
    return 0;
}