#include <cstdio>
#include <algorithm>
#define int long long
template<typename T>
inline T max(const T &a,const T &b){return a>b?a:b;}
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 5e4 + 100;
struct Line
{
    int l,r,x,val;
    bool operator<(const Line &b)
    {
        if(this->x != b.x)
            return this->x < b.x;
        return this->val > b.val;
    }
}E[maxn<<3];
struct node
{
    int l,r,maxx,tag;
}a[maxn<<3];
int T,n,W,H;
int X[maxn],tot;
inline void pushup(const int &p)
{
    a[p].maxx = max(a[p<<1].maxx,a[p<<1|1].maxx);
}
inline void pushdown(const int &p)
{
    node &now = a[p],&ls = a[p<<1],&rs = a[p<<1|1];
    if(!now.tag) return;
    ls.maxx += now.tag,rs.maxx += now.tag;
    ls.tag += now.tag,rs.tag += now.tag;
    now.tag = 0;
}
void modify(const int &p,const int &ll,const int &rr,const int &k)
{
    node &now = a[p],&ls = a[p<<1],&rs = a[p<<1|1];
    if(ll <= now.l && rr >= now.r)
    {
        now.tag += k;
        now.maxx += k;
        return;
    }
    pushdown(p);
    int mid = now.l + now.r >> 1;
    if(ll <= mid) modify(p<<1,ll,rr,k);
    if(rr > mid) modify(p<<1|1,ll,rr,k);
    pushup(p);
}
void build(const int &l,const int &r,const int &p)
{
    a[p].l = l,a[p].r = r,a[p].maxx = a[p].tag = 0;
    if(l == r) 
    {
        a[p<<1].maxx = a[p<<1|1].maxx = 0;
        return;
    }
    int mid = l + r >> 1;
    build(l,mid,p<<1),build(mid + 1,r,p<<1|1);
}
signed main()
{
    read(T);
    while(T--)
    {
        tot = 0;
        read(n),read(W),read(H);
        X[++tot] = 0;
        for(int i = 1;i<=n;++i)
        {
            int a,b,c;
            read(a),read(b),read(c);
            X[++tot] = b,X[++tot] = b + H - 1;
            E[i<<1] = (Line){b,b + H - 1,a,c};
            E[(i<<1) - 1] = (Line){b,b+H-1,a+W-1,-c};
        }
        std::sort(E + 1,E + 1 + n * 2);
        std::sort(X + 1,X + 1 + tot);
        tot = std::unique(X + 1,X + 1 + tot) - X - 1;
        build(1,tot,1);
        int ans = 0;
        for(int i = 1;i<=n*2;++i)
        {
            int l = std::lower_bound(X + 1,X + 1 + tot,E[i].l) - X,r = std::lower_bound(X + 1,X + 1 + tot,E[i].r) - X;
            modify(1,l,r,E[i].val);
            ans = max(ans,a[1].maxx);
        }
        printf("%lld\n",ans);
    }
    return 0;
}