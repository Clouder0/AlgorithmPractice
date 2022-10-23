#include <cstdio>
template<typename T>
void read(T &r)
{
    static char c;static int flag;flag = 1,r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar()) if(c == '-') flag = -1;
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
    r *= flag;
}
template<typename T>
inline T max(const T &a,const T &b){return a>b?a:b;}
using namespace std;
const int maxn = 5e4 + 100;
struct node
{
    int lmax,rmax,mmax,sum;
    int l,r;
}A[maxn<<2];
int a[maxn];
void pushup(node &now,node &ls,node &rs)
{
    now.lmax = max(ls.lmax,ls.sum + rs.lmax);
    now.rmax = max(rs.rmax,rs.sum + ls.rmax);
    now.mmax = max(ls.mmax,rs.mmax);
    now.mmax = max(now.mmax,ls.rmax + rs.lmax);
    now.sum = ls.sum + rs.sum;
}
void build(const int &l,const int &r,const int &p)
{
    A[p].l = l,A[p].r = r;
    if(l == r) return (void)(A[p].lmax = A[p].rmax = A[p].mmax = A[p].sum = a[l]);
    int mid = l + r >> 1;
    build(l,mid,p<<1),build(mid + 1,r,p<<1|1);
    pushup(A[p],A[p<<1],A[p<<1|1]);
}
node ask(const int &p,const int &ll,const int &rr)
{
    node &now = A[p];
    if(now.l >= ll && now.r <= rr) return now;
    int mid = now.l + now.r >> 1;
    if(ll <= mid && rr > mid)
    {
        node lres = ask(p<<1,ll,rr),rres = ask(p<<1|1,ll,rr),res;
        pushup(res,lres,rres);
        return res;
    }
    else if(ll <= mid) return ask(p<<1,ll,rr);
    else return ask(p<<1|1,ll,rr);
}
int n,m;
int main()
{
    read(n);
    for(int i = 1;i<=n;++i) read(a[i]);
    build(1,n,1);
    read(m);
    while(m--)
    {
        int x,y;
        read(x),read(y);
        printf("%d\n",ask(1,x,y).mmax);
    }
    return 0;
}