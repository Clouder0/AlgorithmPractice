#include <cstdio>
#include <algorithm>
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
int read(){int x;read(x);return x;}
const int maxn = 2e6 + 100;
int n,m;
namespace BitTree
{
    long long sum[maxn];
    int vis[maxn],time;
    inline void clear(){++time;}
    inline void add(int x,int k)
    {
        for(;x<=n;x+=x&-x)
        {
            if(vis[x] != time) vis[x] = time,sum[x] = 0;
            sum[x] += k;
        }
    }
    inline long long ask(int x)
    {
        long long res = 0;
        for(;x;x-=x&-x)
        {
            if(vis[x] != time) vis[x] = time,sum[x] = 0;
            res += sum[x];
        }
        return res;
    }
}
struct node
{
    int T,V,P;
}A[maxn],tmp[maxn];
int to[maxn];
long long ans[maxn];
void cdq(int l,int r)
{
    if(l == r) return;
    int mid = l + r >> 1;
    cdq(l,mid),cdq(mid + 1,r);
    int p = l,q = mid + 1,k = l;
    BitTree::clear();
    while(p <= mid && q <= r)
    {
        if (A[p].V > A[q].V)
        {
            BitTree::add(A[p].T,1);
            tmp[k++] = A[p++];
        }
        else
        {
            ans[A[q].T] += BitTree::ask(A[q].T);
            tmp[k++] = A[q++];
        }
    }
    while(p <= mid) tmp[k++] = A[p++];
    while(q <= r) ans[A[q].T] += BitTree::ask(A[q].T),tmp[k++] = A[q++];
    for(int i = l;i<=r;++i) A[i] = tmp[i];
}
void cdq2(int l,int r)
{
    if(l == r) return;
    int mid = l + r >> 1;
    cdq2(l,mid),cdq2(mid + 1,r);
    int p = l,q = mid + 1,k = l;
    BitTree::clear();
    while(p <= mid && q <= r)
    {
        if (A[p].V < A[q].V)
        {
            BitTree::add(A[p].T + 1,1);
            tmp[k++] = A[p++];
        }
        else
        {
            ans[A[q].T] += BitTree::ask(A[q].T);
            tmp[k++] = A[q++];
        }
    }
    while(p <= mid) tmp[k++] = A[p++];
    while(q <= r) ans[A[q].T] += BitTree::ask(A[q].T),tmp[k++] = A[q++];
    for(int i = l;i<=r;++i) A[i] = tmp[i];
}
bool cmp(const node &a,const node &b)
{
    return a.P > b.P;
}

int main()
{
    read(n),read(m);
    for(int i = 1;i<=n;++i) read(A[i].V),A[i].T = 1,A[i].P = i,to[A[i].V] = i;
    for(int i = 1;i<=m;++i) A[to[read()]].T = m - i + 2;
    cdq(1,n);
    std::sort(A + 1,A + 1 +n,cmp);
    cdq2(1,n);
    for(int i = 2;i <= m + 1;++i) ans[i] += ans[i-1];
    for(int i = m + 1;i > 1;--i) printf("%lld\n",ans[i]);
    return 0;
}