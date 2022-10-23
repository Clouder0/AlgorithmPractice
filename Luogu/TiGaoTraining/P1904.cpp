#include <cstdio>
template<typename T>
inline T max(const T &a,const T &b){return a>b?a:b;}
const int maxn = 11000;
int n;
int A[maxn],B[maxn],C[maxn];
int maxx[maxn<<2],tag[maxn<<2];
inline void pushup(const int &p){maxx[p] = max(maxx[p<<1],maxx[p<<1|1]);}
inline void pushdown(const int &p)
{
    if(!tag[p]) return;
    maxx[p<<1] = max(maxx[p<<1],tag[p]);
    maxx[p<<1|1] = max(maxx[p<<1|1],tag[p]);
    tag[p<<1] = max(tag[p<<1],tag[p]);
    tag[p<<1|1] = max(tag[p<<1|1],tag[p]);
    tag[p] = 0;
}
void modify(const int &l,const int &r,const int &p,const int &ll,const int &rr,const int &k)
{
    if(ll <= l && rr >= r)
    {
        tag[p] = max(tag[p],k);
        maxx[p] = max(maxx[p],k);
        return;
    }
    pushdown(p);
    int mid = l + r >> 1;
    if(ll <= mid) modify(l,mid,p<<1,ll,rr,k);
    if(rr > mid) modify(mid + 1,r,p<<1|1,ll,rr,k);
    pushup(p);
}
int h[maxn];
void output(const int &l,const int &r,const int &p)
{
    if(l == r)
    {
        h[l] = maxx[p];
        return;
    }
    pushdown(p);
    int mid = l + r >> 1;
    output(l,mid,p<<1),output(mid + 1,r,p<<1|1);
}
int maxl;
int main()
{
    int a,b,c;
    while(scanf("%d %d %d",&a,&b,&c) != EOF)
    {
        ++n;
        A[n] = a,B[n] = b,C[n] = c;
        maxl = maxl>c?maxl:c;
    }
    for(int i = 1;i<=n;++i) 
        modify(1,maxl,1,A[i],C[i] - 1,B[i]);
    output(1,maxl,1);
    for(int i = 1;i<=maxl;++i)
        if(h[i] != h[i-1]) printf("%d %d ",i,h[i]);
    return 0;
}