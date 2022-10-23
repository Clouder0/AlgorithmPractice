#include <cstdio>
#include <cmath>
#include <algorithm>
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 5e4 + 100;
int n,m;
int a[maxn];
struct query
{
    int l,r,pos,id;
}Q[maxn];
long long cnt[maxn],ans1[maxn],ans2[maxn];
bool cmp(const query &a,const query &b)
{
    if(a.pos != b.pos) return a.pos < b.pos;
    if(a.pos & 1) return a.r < b.r;
    else return a.r > b.r;
}
long long gcd(long long a,long long b) {return b == 0 ? a : gcd(b,a % b);}
int main()
{
    read(n),read(m);
    int size = (int)std::sqrt(n);
    for(int i = 1;i<=n;++i) read(a[i]);
    for(int i = 1;i<=m;++i) read(Q[i].l),read(Q[i].r),Q[i].pos = Q[i].l / size,Q[i].id = i;
    std::sort(Q + 1,Q + 1 + m,cmp);
    int l = 1,r = 0;
    long long t = 0;
    for(int i = 1;i<=m;++i)
    {
        if(Q[i].l == Q[i].r) continue;
        while(l > Q[i].l) --l,t -= cnt[a[l]] * cnt[a[l]],cnt[a[l]]++,t += cnt[a[l]] * cnt[a[l]];
        while(r < Q[i].r) ++r,t -= cnt[a[r]] * cnt[a[r]],cnt[a[r]]++,t += cnt[a[r]] * cnt[a[r]];
        while(l < Q[i].l) t -= cnt[a[l]] * cnt[a[l]],--cnt[a[l]],t += cnt[a[l]] * cnt[a[l]],++l;
        while(r > Q[i].r) t -= cnt[a[r]] * cnt[a[r]],--cnt[a[r]],t += cnt[a[r]] * cnt[a[r]],--r;
        ans1[Q[i].id] = t - (r - l + 1);
        ans2[Q[i].id] = 1ll * (r - l + 1) * (r - l);
    }
    for(int i = 1;i<=m;++i)
    {
        if(ans1[i] <= 0) puts("0/1");
        else
        {
            long long g = gcd(ans1[i], ans2[i]);
            ans1[i] /= g,ans2[i] /= g;
            printf("%lld/%lld\n",ans1[i],ans2[i]);
        }
    }
    return 0;
}