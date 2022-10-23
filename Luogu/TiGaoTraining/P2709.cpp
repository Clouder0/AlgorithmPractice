#include <cstdio>
#include <algorithm>
#include <cmath>
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn =  5e4 + 100;
int n,m,k;
int a[maxn];
long long ANS[maxn];
struct node
{
    int l,r,id,pos;
}Q[maxn];
bool cmp(const node &a,const node &b)
{
    if(a.pos != b.pos) return a.pos < b.pos;
    if(a.pos & 1) return a.r < b.r;
    else return a.r > b.r;
}
int c[maxn];
signed main()
{
    read(n),read(m),read(k);
    int size = (int)std::sqrt(n);
    for(int i = 1;i<=n;++i) read(a[i]);
    for(int i = 1;i<=m;++i) read(Q[i].l),read(Q[i].r),Q[i].id = i,Q[i].pos = Q[i].l / size;
    std::sort(Q + 1,Q + 1 + m,cmp);
    int l = 1,r = 0;
    long long ans = 0;
    for(int i = 1;i<=m;++i)
    {
        while(l > Q[i].l) --l,ans -= c[a[l]] * c[a[l]],c[a[l]]++,ans += c[a[l]] * c[a[l]];
        while(r < Q[i].r) ++r,ans -= c[a[r]] * c[a[r]],c[a[r]]++,ans += c[a[r]] * c[a[r]];
        while(l < Q[i].l) ans -= c[a[l]] * c[a[l]],c[a[l]]--,ans += c[a[l]] * c[a[l]],++l;
        while(r > Q[i].r) ans -= c[a[r]] * c[a[r]],c[a[r]]--,ans += c[a[r]] * c[a[r]],--r;
        ANS[Q[i].id] = ans;
    }
    for(int i = 1;i<=m;++i) printf("%lld\n",ANS[i]);
    return 0;
}