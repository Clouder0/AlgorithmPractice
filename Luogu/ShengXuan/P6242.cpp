#include <cstdio>
#define ls p<<1
#define rs p<<1|1
template<typename T>
inline T max(const T &a,const T &b){return a>b?a:b;}
template<typename T>
void read(T &r)
{
    static char c;static int flag;flag = 1,r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar()) if(c == '-') flag = -1;
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
    r *= flag;
}
const long long INF = 1ll<<60;
const int maxn = 5e5 + 100;
int n,m;
int origin[maxn];
struct node
{
    int l,r;
    long long first_max,second_max,history_max,cnt,sum;
    long long history_max_tag,history_tag,max_tag,tag;
}A[maxn<<2];
inline void update(const int &p,const int &k1,const int &k1_,const int &k2,const int &k2_)
{
    A[p].sum += 1ll * k1 * A[p].cnt + 1ll * k2 * (A[p].r - A[p].l + 1 - A[p].cnt);
    A[p].history_max = max(A[p].history_max,A[p].first_max + k1_);
    A[p].history_max_tag = max(A[p].history_max_tag,A[p].max_tag + k1_);
    A[p].first_max += k1,A[p].max_tag += k1;
    A[p].history_tag = max(A[p].history_tag,A[p].tag + k2_);
    if(A[p].second_max != -INF) A[p].second_max += k2;
    A[p].tag += k2;
}
inline void pushup(const int &p)
{
    A[p].sum = A[ls].sum + A[rs].sum;
    A[p].history_max = max(A[ls].history_max,A[rs].history_max);
    if(A[ls].first_max == A[rs].first_max)
    {
        A[p].first_max = A[ls].first_max;
        A[p].second_max = max(A[ls].second_max,A[rs].second_max);
        A[p].cnt = A[ls].cnt + A[rs].cnt;
    }
    else if(A[ls].first_max > A[rs].first_max)
    {
        A[p].first_max = A[ls].first_max;
        A[p].second_max = max(A[ls].second_max,A[rs].first_max);
        A[p].cnt = A[ls].cnt;
    }
    else
    {
        A[p].first_max = A[rs].first_max;
        A[p].second_max = max(A[rs].second_max,A[ls].first_max);
        A[p].cnt = A[rs].cnt;
    }
}
inline void pushdown(const int &p)
{
    long long maxx = max(A[ls].first_max,A[rs].first_max);
    if(A[ls].first_max == maxx) update(ls,A[p].max_tag,A[p].history_max_tag,A[p].tag,A[p].history_tag);
    else update(ls,A[p].tag,A[p].history_tag,A[p].tag,A[p].history_tag);
    if (A[rs].first_max == maxx) update(rs, A[p].max_tag, A[p].history_max_tag, A[p].tag, A[p].history_tag);
    else update(rs,A[p].tag,A[p].history_tag,A[p].tag,A[p].history_tag);
    A[p].max_tag = A[p].history_max_tag = A[p].tag = A[p].history_tag = 0;
}
void build(int l,int r,int p)
{
    A[p].l = l,A[p].r = r;
    if(l == r)
    {
        A[p].first_max = A[p].history_max = A[p].sum = origin[l];
        A[p].cnt = 1;
        A[p].second_max = -INF;
        return;
    }
    int mid = l + r >> 1;
    build(l,mid,ls),build(mid + 1,r,rs);
    pushup(p);
}
void add(int p,int ll,int rr,int k)
{
    if(A[p].l >= ll && A[p].r <= rr)
    {
        update(p,k,k,k,k);
        return;
    }
    pushdown(p);
    if(ll <= A[ls].r) add(ls,ll,rr,k);
    if(rr >= A[rs].l) add(rs,ll,rr,k);
    pushup(p);
}
void modify(int p,int ll,int rr,int k)
{
    if(k >= A[p].first_max) return;
    if(A[p].l >= ll && A[p].r <= rr && k > A[p].second_max)
    {
        update(p,k - A[p].first_max,k - A[p].first_max,0,0);
        return;
    }
    pushdown(p);
    if(ll <= A[ls].r) modify(ls,ll,rr,k);
    if(rr >= A[rs].l) modify(rs,ll,rr,k);
    pushup(p);
}
long long asksum(int p,int ll,int rr)
{
    if(A[p].l >= ll && A[p].r <= rr) return A[p].sum;
    pushdown(p);
    long long res = 0;
    if(ll <= A[ls].r) res += asksum(ls,ll,rr);
    if(rr >= A[rs].l) res += asksum(rs,ll,rr);
    return res;
}
long long askmax(int p,int ll,int rr)
{
    if(A[p].l >= ll && A[p].r <= rr) return A[p].first_max;
    pushdown(p);
    long long res = -INF;
    if(ll <= A[ls].r) res = askmax(ls,ll,rr);
    if(rr >= A[rs].l) res = max(res,askmax(rs,ll,rr));
    return res;
}
long long askhistorymax(int p,int ll,int rr)
{
    if(A[p].l >= ll && A[p].r <= rr) return A[p].history_max;
    pushdown(p);
    long long res = -INF;
    if(ll <= A[ls].r) res = askhistorymax(ls,ll,rr);
    if(rr >= A[rs].l) res = max(res,askhistorymax(rs,ll,rr));
    return res;
}
int main()
{
    read(n),read(m);
    for(int i = 1;i<=n;++i) read(origin[i]);
    build(1,n,1);
    while(m--)
    {
        int opt,l,r,k;
        read(opt);
        read(l), read(r);
        if (opt == 1) read(k),add(1,l,r,k);
        else if(opt == 2) read(k),modify(1,l,r,k);
        else if(opt == 3) printf("%lld\n",asksum(1,l,r));
        else if(opt == 4) printf("%lld\n",askmax(1,l,r));
        else printf("%lld\n",askhistorymax(1,l,r));
    }
    return 0;
}