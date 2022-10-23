#include <cstdio>
const int maxn = 4e5 + 10;
#define ls p << 1
#define rs p << 1 | 1
const int mod = 571373;
int n,m,a[maxn],sum[maxn], addtag[maxn], multag[maxn];
inline void pushdown(int l, int r, int p)
{
    if(multag[p] == 1 && addtag[p] == 0) return;
    if(multag[p] != 1)
    {
        sum[ls] = (1ll * sum[ls] * multag[p]) % mod;
        sum[rs] = (1ll * sum[rs] * multag[p]) % mod;
        addtag[ls] = (1ll * addtag[ls] * multag[p]) % mod;
        multag[ls] = (1ll * multag[ls] * multag[p]) % mod;
        addtag[rs] = (1ll * addtag[rs] * multag[p]) % mod;
        multag[rs] = (1ll * multag[rs] * multag[p]) % mod;
        multag[p] = 1;
    }
    if(addtag[p])
    {
        int mid = (l + r) >> 1;
        sum[ls] = (sum[ls] + 1ll * addtag[p] * (mid - l + 1)) % mod;
        sum[rs] = (sum[rs] + 1ll * addtag[p] * (r - mid)) % mod;
        addtag[ls] = (addtag[ls] + addtag[p]) % mod;
        addtag[rs] = (addtag[rs] + addtag[p]) % mod;
        addtag[p] = 0;
    }
}
inline void pushup(int p)
{
    sum[p] = (sum[ls] + sum[rs]) % mod;
}
void mul(int l,int r,int p,int ll,int rr, int k)
{
    if(l >= ll && r <= rr)
    {
        sum[p] = (1ll * sum[p] * k) % mod;
        addtag[p] = (1ll * addtag[p] * k) % mod;
        multag[p] = (1ll * multag[p] * k) % mod;
        return;
    }
    pushdown(l, r, p);
    int mid = (l + r) >> 1;
    if (ll <= mid) mul(l, mid, ls, ll, rr, k);
    if (rr > mid) mul(mid + 1, r, rs, ll, rr, k);
    pushup(p);
}
void add(int l, int r, int p, int ll, int rr, int k)
{
    if(l >= ll && r <= rr)
    {
        sum[p] = (sum[p] + 1ll * (r - l + 1) * k) % mod;
        addtag[p] = (addtag[p] + k) % mod;
        return;
    }
    pushdown(l,r,p);
    int mid = (l + r) >> 1;
    if(ll <= mid) add(l,mid,ls,ll,rr,k);
    if(rr > mid) add(mid+1,r,rs,ll,rr,k);
    pushup(p);
}
int ask(int l,int r,int p,int ll,int rr)
{
    if(l >= ll && r<= rr) return sum[p];
    pushdown(l,r,p);
    int res = 0;
    int mid = (l + r) >> 1;
    if(ll <= mid) res = ask(l,mid,ls,ll,rr);
    if(rr > mid) res = (res + ask(mid + 1,r,rs,ll,rr)) % mod;
    return res;
}
void build(int l, int r, int p)
{
    multag[p] = 1;
    if (l == r) return (void)(sum[p] = a[l]);
    int mid = (l + r) >> 1;
    build(l, mid, ls), build(mid + 1, r, rs), pushup(p);
}
int main()
{
    int t;
    scanf("%d%d%d",&n,&m,&t);
    for (int i = 1; i <= n; ++i) scanf("%d",a + i);
    build(1,n,1);
    while(m--)
    {
        int opt, l, r, k;
        scanf("%d%d%d",&opt,&l,&r);
        if(opt == 3) printf("%d\n",ask(1,n,1,l,r));
        else
        {
            scanf("%d", &k);
            if (opt == 1)
                mul(1, n, 1, l, r, k);
            else
                add(1, n, 1, l, r, k);
        }
    }
    return 0;
}