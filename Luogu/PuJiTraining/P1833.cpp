#include <cstdio>
template<typename T>
inline T max(const T &a,const T &b){return a>b?a:b;}
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 1e4 + 10;
int n,m;
int w[maxn],v[maxn],num[maxn];
int f[maxn];
int main()
{
    int a,b,c,d;
    read(a);
    read(b);
    read(c);
    read(d);
    read(n);
    m = (c - a) * 60 + d - b;
    for(int i = 1;i<=n;++i)
        read(w[i]),read(v[i]),read(num[i]);
    for(int i = 1;i<=n;++i)
    {
        if(num[i] == 0)
        {
            for(int j = w[i];j<=m;++j)
                f[j] = max(f[j],f[j-w[i]] + v[i]);
            continue;
        }
        for(int k = 1;k<=num[i];num[i] -= k,k<<=1)
        {
            int weight = w[i] * k,value = v[i] * k;
            for(int j = m;j>=weight;--j)
                f[j] = max(f[j],f[j-weight] + value);
        }
        if(num[i])
        {
            int weight = w[i] * num[i],value = v[i] * num[i];
            for(int j = m;j>=weight;--j)
                f[j] = max(f[j],f[j-weight] + value);
        }
    }
    int ans = 0;
    for(int i = 0;i<=m;++i)
        ans = max(ans,f[i]);
    printf("%d",ans);
    return 0;
}