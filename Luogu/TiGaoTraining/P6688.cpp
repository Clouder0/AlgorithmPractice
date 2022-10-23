#include <cstdio>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
inline char nc()
{
    #ifdef DEBUG
    return getchar();
    #endif
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
inline void read(char *s)
{
    static char c;
    for (; !isalpha(c); c = nc());
    for (; isalpha(c); c = nc()) *s++ = c;
    *s = '\0';
}
template<typename T>
inline T read(T &r)
{
    static char c;
    static int flag;
    flag = 1, r = 0;
    for (c = nc(); !isdigit(c); c = nc()) if (c == '-') flag = -1;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r *= flag;
}
const int maxn = 1e6 + 100;
const int mod = 1e9 + 7;
const int bot = 195123;
int n,m;
inline int mul(const int a,const int b){return (1ll * a * b) % mod;}
inline int add(const int a,const int b)
{
    int res = a + b;
    if(res >= mod) res -= mod;
    else if(res < 0) res += mod;
    return res;
}
inline int fastpow(int x,int k)
{
    int res = 1;
    for(;k;k>>=1)
    {
        if(k & 1) res = mul(res,x);
        x = mul(x,x);
    }
    return res;
}
struct node
{
    long long sum,powsum;
    int oddnum;
}A[maxn<<2];
int a[maxn];
inline void pushup(node &now,node &ls,node &rs)
{
    now.sum = ls.sum + rs.sum;
    now.powsum = add(ls.powsum,rs.powsum);
    now.oddnum = ls.oddnum + rs.oddnum;
}
void build(int l,int r,int p)
{
    node &now = A[p];
    if(l == r) return (void)(now.sum = a[l],now.powsum = fastpow(bot,a[l]),now.oddnum = a[l] & 1);
    int mid = l + r >> 1;
    build(l,mid,p<<1),build(mid + 1,r,p<<1|1);
    pushup(A[p],A[p<<1],A[p<<1|1]);
}
void modify(int l,int r,int p,int pos,int k)
{
    node &now = A[p],&ls = A[p<<1],&rs = A[p<<1|1];
    if(l == r) return (void)(now.sum = k,now.powsum = fastpow(bot,k),now.oddnum = k & 1);
    int mid = l + r >> 1;
    if(pos <= mid) modify(l,mid,p<<1,pos,k);
    else modify(mid + 1,r,p<<1|1,pos,k);
    pushup(now,ls,rs);
}
node ask(int l,int r,int p,int ll,int rr)
{
    node &now = A[p];
    if(l >= ll && r <= rr) return now;
    int mid = l + r >> 1;
    if(ll <= mid && rr > mid)
    {
        node lres = ask(l,mid,p<<1,ll,rr),rres = ask(mid + 1,r,p<<1|1,ll,rr),res;
        pushup(res,lres,rres);
        return res;
    }
    else if(ll <= mid) return ask(l,mid,p<<1,ll,rr);
    else return ask(mid + 1,r,p<<1|1,ll,rr);
}
int main()
{
    read(n),read(m);
    for (int i = 1; i <= n; ++i) read(a[i]);
    build(1,n,1);
    while(m--)
    {
        int opt;
        read(opt);
        if(opt == 0)
        {
            int x,y;
            read(x),read(y),modify(1,n,1,x,y);
        }
        else
        {
            int l1,r1,l2,r2,len;
            read(l1), read(r1), read(l2), read(r2);
            len = r1 - l1 + 1;
            node res1 = ask(1, n, 1, l1, r1), res2 = ask(1, n, 1, l2, r2);
            if(res1.sum > res2.sum) std::swap(l1,l2),std::swap(r1,r2),std::swap(res1,res2);
            long long sv = res2.sum - res1.sum;
            if(sv % len) 
            {
                puts("NO");
                continue;
            }
            sv /= len;
            if(sv & 1) 
            {
                if(len - res1.oddnum != res2.oddnum) 
                {
                    puts("NO");
                    continue;
                }
            }
            else
            {
                if(res1.oddnum != res2.oddnum) 
                {
                    puts("NO");
                    continue;
                }
            }
            long long val = fastpow(bot,sv);
            if(mul(val,res1.powsum) != res2.powsum)
            {
                puts("NO");
                continue;
            }
            puts("YES");
        }
    }
    return 0;
}