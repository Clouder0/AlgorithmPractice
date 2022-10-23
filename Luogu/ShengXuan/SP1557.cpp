#include <cstdio>
#include <algorithm>
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
const int maxn = 1e5 + 100;
int n,m;
int last[maxn*3],pre[maxn],a[maxn],ANS[maxn];
struct query
{
    int l,r,id;
    bool operator<(const query &b) const {return r < b.r;}
}Q[maxn];
struct node
{
    int l,r,val,tag,hval,htag;
}A[maxn<<2];
inline void pushdown(node &now,node &ls,node &rs)
{
    if(now.tag == 0 && now.htag == 0) return;
    ls.htag = max(ls.htag,ls.tag + now.htag);
    rs.htag = max(rs.htag,rs.tag + now.htag);
    ls.hval = max(ls.hval,ls.val + now.htag);
    rs.hval = max(rs.hval,rs.val + now.htag);
    ls.tag += now.tag;
    rs.tag += now.tag;
    ls.val += now.tag;
    rs.val += now.tag;
    now.tag = now.htag = 0;
}
inline void pushup(node &now,node &ls,node &rs)
{
    now.val = max(ls.val,rs.val);
    now.hval = max(ls.hval,rs.hval);
}
void build(const int &l,const int &r,const int &p)
{
    A[p].l = l,A[p].r = r;
    if(l == r) return;
    int mid = l + r >> 1;
    build(l,mid,p<<1),build(mid + 1,r,p<<1|1);
}
void modify(const int &p,const int &ll,const int &rr,const int &k)
{
    node &now = A[p],&ls = A[p<<1],&rs = A[p<<1|1];
    if(now.l >= ll && now.r <= rr)
    {
        now.val += k;
        now.tag += k;
        now.hval = max(now.val,now.hval);
        now.htag = max(now.htag,now.tag);
        return;
    }
    pushdown(now,ls,rs);
    if(ll <= ls.r) modify(p<<1,ll,rr,k);
    if(rr >= rs.l) modify(p<<1|1,ll,rr,k);
    pushup(now,ls,rs);
}
int ask(const int &p,const int &ll,const int &rr)
{
    node &now = A[p],&ls = A[p<<1],&rs = A[p<<1|1];
    if(now.l >= ll && now.r <= rr) return now.hval;
    pushdown(now,ls,rs);
    int res = 0;
    if(ll <= ls.r) res = ask(p<<1,ll,rr);
    if(rr >= rs.l) res = max(res,ask(p<<1|1,ll,rr));
    return res;
    
}
int main()
{
    read(n);
    for(int i = 1;i<=n;++i) read(a[i]),pre[i] = last[a[i] + maxn],last[a[i] + maxn] = i;
    build(1,n,1);
    read(m);
    for(int i = 1;i<=m;++i) Q[i].id = i,read(Q[i].l),read(Q[i].r);
    std::sort(Q + 1,Q + 1 + m);
    int p = 1;
    for(int i = 1;i<=m;++i)
    {
        while(p <= Q[i].r) modify(1,pre[p] + 1,p,a[p]),++p;
        ANS[Q[i].id] = ask(1,Q[i].l,Q[i].r);
    }
    for(int i = 1;i<=m;++i) printf("%d\n",ANS[i]);
    return 0;
}