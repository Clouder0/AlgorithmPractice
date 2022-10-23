#include <cstdio>
#include <ctype.h>
template<typename T>
inline void read(T &r)
{
    static char c;static int flag;
    r = 0,flag = 1;
    for(c = getchar();!isdigit(c);c = getchar()) if(c == '-') flag = -1;
    for(;isdigit(c);c=getchar()) r = r * 10 + c - 48;
    r *= flag;
}
template<typename T>
inline T max(const T &a,const T &b){return a>b?a:b;}
const int maxn = 1e4 + 100;
struct node
{
    int l,r,lmax,rmax,mmax,sum;
}A[maxn<<2];
int a[maxn],sum[maxn];
inline void pushup(node &now,node &ls,node &rs)
{
    now.sum = ls.sum + rs.sum;
    now.lmax = max(ls.lmax,ls.sum + rs.lmax);
    now.rmax = max(rs.rmax,rs.sum + ls.rmax);
    now.mmax = max(ls.mmax,rs.mmax);;
    now.mmax = max(now.mmax,ls.rmax + rs.lmax);
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
    if(ll > rr) return node();
    node &now = A[p],&ls = A[p<<1],&rs = A[p<<1|1];
    if(now.l >= ll && now.r <= rr) return now;
    if(ll <= ls.r && rr >= rs.l)
    {
        node la = ask(p<<1,ll,rr),ra = ask(p<<1|1,ll,rr),res;
        res.lmax = res.rmax = res.mmax = -(1<<30);
        pushup(res,la,ra);
        return res;
    }
    else if(ll <= ls.r) return ask(p<<1,ll,rr);
    else return ask(p<<1|1,ll,rr);
}
int n,m,T;
int main()
{
    read(T);
    while(T--)
    {
        read(n);
        for (int i = 1; i <= n; ++i) read(a[i]), sum[i] = sum[i - 1] + a[i];
        build(1, n, 1);
        read(m);
        while (m--)
        {
            int l1, r1, l2, r2;
            read(l1), read(r1), read(l2), read(r2);
            if (r1 < l2) printf("%d\n", sum[l2 - 1] - sum[r1] + ask(1, l1, r1).rmax + ask(1, l2, r2).lmax);
            else
            {
                node left = ask(1, l1, l2 - 1), mid = ask(1, l2, r1), right = ask(1, r1 + 1, r2);
                int t = -(1 << 30);
                t = max(t, left.rmax + mid.lmax);
                t = max(t, left.rmax + mid.sum + right.lmax);
                t = max(t, mid.mmax);
                t = max(t, mid.rmax + right.lmax);
                printf("%d\n", t);
            }
        }
    }
    return 0;
}