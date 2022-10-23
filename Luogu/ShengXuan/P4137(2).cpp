#include <cstdio>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
#define DEBUG
inline char nc()
{
    #ifdef DEBUG
    return getchar();
    #endif
    static char buf[bufSize],*p1 = buf,*p2 = buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,bufSize,stdin),p1==p2)?EOF:*p1++;
}
template<typename T>
inline T read(T &r)
{
    static char c;
    r=0;
    for(c = nc();!isdigit(c);) c = nc();
    for(;isdigit(c);c=nc()) r = r * 10 + c - 48;
    return r;
}
const int maxn = 2e5 + 100;
int n,m;
int L[maxn<<5],R[maxn<<5],val[maxn<<5],root[maxn],cnt;
void modify(const int &l,const int &r,int &p,const int &pre,const int &pos,const int &k)
{
    p = ++cnt;
    L[p] = L[pre],R[p] = R[pre],val[p] = val[pre];
    if(l == r) return (void)(val[p] = k);
    int mid = l + r >> 1;
    if(pos <= mid) modify(l,mid,L[p],L[pre],pos,k);
    else modify(mid + 1,r,R[p],R[pre],pos,k);
    val[p] = std::min(val[L[p]],val[R[p]]);
}
int ask(const int &l,const int &r,const int &p,const int &k)
{
    if(!p || l == r) return l;
    int mid = l + r >> 1;
    if(val[L[p]] < k) return ask(l,mid,L[p],k);
    else return ask(mid + 1,r,R[p],k);
}
int a[maxn];
int main()
{
//    freopen("test.in","r",stdin);
    read(n),read(m);
    for(int i = 1;i<=n;++i) read(a[i]);
    for(int i = 1;i<=n;++i) if(a[i] <= n) modify(1,n + 2,root[i],root[i-1],a[i] + 1,i); else root[i] = root[i-1];
    while(m--)
    {
        int l,r;
        read(l),read(r);
        printf("%d\n", ask(1, n + 2, root[r], l) - 1);
    }
    return 0;
}