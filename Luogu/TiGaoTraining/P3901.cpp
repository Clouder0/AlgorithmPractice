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
const int maxn = 1e5 + 100;
int n,m,t,l,r;
int last[maxn],f[maxn];
int main()
{
    read(n),read(m);
    for(int i = 1;i<=n;++i) read(t),f[i] = max(f[i-1],last[t]),last[t] = i;
    while(m--) read(l),read(r),printf((f[r] >= l ? "No\n" : "Yes\n"));
    return 0;
}