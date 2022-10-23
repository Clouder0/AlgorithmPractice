#include <cstdio>
#include <algorithm>
#include <cmath>
#define int long long
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 5e4 + 100;
struct node
{
    int l,r,pos,id,k;
    bool operator<(const node &b) const
    {
        if(pos != b.pos) return pos < b.pos;
        return pos & 1 ? r < b.r : r > b.r;
    }
}Q[maxn*4];
int tot,ANS[maxn];
int n,m,a[maxn];
int lcnt[maxn],rcnt[maxn];
signed main()
{
    read(n);
    for(int i = 1;i<=n;++i) read(a[i]);
    read(m);
    int size = n / sqrt(m * 4);
    for(int i = 1;i<=m;++i)
    {
        int l1,r1,l2,r2;
        read(l1),read(r1),read(l2),read(r2);
        Q[++tot].id = i, Q[tot].l = r1, Q[tot].r = r2, Q[tot].k = 1, Q[tot].pos = Q[tot].l / size;
        Q[++tot].id = i, Q[tot].l = l1 - 1, Q[tot].r = r2, Q[tot].k = -1, Q[tot].pos = Q[tot].l / size;
        Q[++tot].id = i, Q[tot].l = l2 - 1, Q[tot].r = r1, Q[tot].k = -1, Q[tot].pos = Q[tot].l / size;
        Q[++tot].id = i, Q[tot].l = l1 - 1, Q[tot].r = l2 - 1, Q[tot].k = 1, Q[tot].pos = Q[tot].l / size;
    }
    std::sort(Q + 1,Q + 1 + tot);
    int l = 0,r = 0,ans = 0,lans = 0,rans = 0;
    for(int i = 1;i<=tot;++i)
    {
        while(l < Q[i].l) 
        {
            ++l;
            ans -= lcnt[a[l]] * rcnt[a[l]];
            ans += ++lcnt[a[l]] * rcnt[a[l]];
        }
        while(r < Q[i].r)
        {
            ++r;
            ans -= lcnt[a[r]] * rcnt[a[r]];
            ans += lcnt[a[r]] * ++rcnt[a[r]];
        }
        while(l > Q[i].l)
        {
            ans -= lcnt[a[l]] * rcnt[a[l]];
            ans += --lcnt[a[l]] * rcnt[a[l]];
            --l;
        }
        while(r > Q[i].r)
        {
            ans -= lcnt[a[r]] * rcnt[a[r]];
            ans += lcnt[a[r]] * --rcnt[a[r]];
            --r;
        }
        ANS[Q[i].id] += ans * Q[i].k;
    }
    for(int i = 1;i<=m;++i) printf("%lld\n",ANS[i]);
    return 0;
}