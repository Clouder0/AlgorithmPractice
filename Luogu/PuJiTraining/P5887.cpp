#include <cstdio>
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 1e6 + 100;
int gcd(int a,int b)
{
    return b == 0 ? a : gcd(b,a%b);
}
int n,m,k;
int a[maxn],color[maxn],vis[maxn];
int main()
{
    read(n),read(m),read(k);
    int colornum = gcd(n,k);
    for(int i = 0;i<=n;++i) color[i] = i % colornum;
    for(int i = 1;i<=m;++i) read(a[i]),vis[color[a[i]]] = 1;
    int ans = 0;
    for(int i = 0;i<colornum;++i) ans += !vis[i];
    printf("%d",1ll * ans * n / colornum);
    return 0;
}