#include <cstdio>
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
template<typename T>
inline T min(const T &a,const T &b){return a<b?a:b;}
const int maxn = 1e5 + 100;
int n,k;
long long f[maxn],sum;
int a[maxn];
int q[maxn],head = 1,tail;
int main()
{
    read(n),read(k);
    for(int i = 1;i<=n;++i) read(a[i]),sum += a[i];
    int p = 1;
    q[++tail] = 0;
    for(int i = 1;i<=n;++i)
    {
        while(tail >= head && f[i-1] < f[q[tail]]) --tail;
        q[++tail] = i-1;
        while(tail >= head && q[head] < i - k - 1) ++head;
        f[i] = f[q[head]] + a[i];
    }
    long long ans = 1ll<<60;
    for(int i = n - k;i<=n;++i) ans = min(f[i],ans);
    printf("%lld",sum - ans);
    return 0;
}