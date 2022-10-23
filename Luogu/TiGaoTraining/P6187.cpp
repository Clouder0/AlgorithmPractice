#include <cstdio>
#include <algorithm>
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 2e5 + 100;
int n,m;
int a[maxn];
long long f[maxn];
int gcd(int a,int b){return b == 0 ? a : gcd(b,a%b);}
int tmp[maxn];
long long calc(int k)
{
    int num = gcd(n,k),length = n / num;
    if(f[num] != 0) return f[num];
    int l = 1,r = length;
    for(int i = 1;i<=num;++i)
    {
        int p = 0;
        for(int i = 1;i<length;i+=2) tmp[++p] = i;
        tmp[++p] = length;
        if(tmp[p] - tmp[p-1] == 2) for(int i = length - 1;i>0;i-=2) tmp[++p] = i;
        else for(int i = length - 2;i>0;i-=2) tmp[++p] = i;
        for(int i = 1;i<p;++i) 
            f[num] += 1ll * a[l + tmp[i] - 1] * a[l + tmp[i + 1] - 1];
        f[num] += 1ll * a[l + tmp[1] - 1] * a[l + tmp[p] - 1];
        l = r + 1,r = l + length - 1;
    }
    return f[num];
}
int main()
{
    read(n),read(m);
    for(int i = 1;i<=n;++i) read(a[i]),f[n] += 1ll * a[i] * a[i];
    std::sort(a + 1,a + 1 + n);
    while(m--)
    {
        int k;
        read(k);
        if(k == 0)
        {
            printf("%lld\n",f[n]);
            continue;
        }
        else if(n == 1)
        {
            printf("%lld\n",1ll * a[1] * a[1]);
            continue;
        }
        printf("%lld\n",calc(k));
    }
    return 0;
}