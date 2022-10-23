
#include <cstdio>
#include <algorithm>
const int bufSize = 1e6;
inline char nc()
{
    static char buf[bufSize],*p1 = buf,*p2 = buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,bufSize,stdin),p1==p2)?EOF:*p1++;
}
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=nc();c>'9'||c<'0';c=nc());
    for(;c>='0'&&c<='9';c=nc()) r = r * 10 + c - 48;
}
const int maxn = 1e5 + 100,maxm = 1e5 + 100,maxtot = 5e5 + 100;
struct node
{
    int type,x,y,z,k,id;
}A[maxtot],B[maxtot];
int tot;
bool cmpx(const node &a,const node &b)
{
    if(a.x != b.x) return a.x < b.x;
    return a.type < b.type;
}
bool cmpy(const node &a,const node &b)
{
    if(a.y != b.y) return a.y < b.y;
    return a.type < b.type;
}
int n,m,last[maxn],ans1[maxm],ans2[maxm];
namespace Bit
{
    inline int lowbit(const int &x){return x & -x;}
    int sum[maxn],vis[maxn],cnt;
    inline void clear(){++cnt;}
    inline void check(int x){if(vis[x] != cnt) vis[x] = cnt,sum[x] = 0;}
    inline void add(int x,int k) {++x;while(x <= n + 1) check(x),sum[x] += k,x += lowbit(x);}
    inline int ask(int x)
    {
        ++x;
        int res = 0;
        while(x) check(x),res += sum[x],x -= lowbit(x);
        return res;
    }
}
void cdq(const int l,const int r)
{
    if(l == r) return;
    int mid = l + r >> 1;
    cdq(l,mid),cdq(mid + 1,r);
    int p = l,q = mid + 1,k = l;
    int tmp = 0;
    Bit::clear();
    while(p <= mid && q <= r)
    {
        if(A[p].y <= A[q].y) 
        {
            if(A[p].type == 0) Bit::add(A[p].z,1),++tmp;
            B[k++] = A[p++];
        }
        else
        {
            if(A[q].type == 1) ans1[A[q].id] += A[q].k * tmp,ans2[A[q].id] += A[q].k * Bit::ask(A[q].z);
            B[k++] = A[q++];
        }
    }
    while(p <= mid) B[k++] = A[p++];
    while(q <= r)
    {
        if(A[q].type == 1) ans1[A[q].id] += A[q].k * tmp,ans2[A[q].id] += A[q].k * Bit::ask(A[q].z);
        B[k++] = A[q++];
    }
    for(int i = l;i<=r;++i) A[i] = B[i];
}
int main()
{
    read(n),read(m);
    for(int i = 1;i<=n;++i)
    {
        int val;
        read(val);
        A[++tot].type = 0,A[tot].x = i,A[tot].y = val,A[tot].z = last[val];
        last[val] = i;
    }
    for(int i = 1;i<=m;++i)
    {
        int l,r,a,b;
        read(l),read(r),read(a),read(b);
        A[++tot].type = 1, A[tot].x = l - 1, A[tot].y = b, A[tot].z = l - 1, A[tot].id = i, A[tot].k = -1;
        A[++tot].type = 1, A[tot].x = r, A[tot].y = b, A[tot].z = l - 1, A[tot].id = i, A[tot].k = 1;
        A[++tot].type = 1, A[tot].x = l - 1, A[tot].y = a - 1, A[tot].z = l - 1, A[tot].id = i, A[tot].k = 1;
        A[++tot].type = 1, A[tot].x = r, A[tot].y = a - 1, A[tot].z = l - 1, A[tot].id = i, A[tot].k = -1;
    }
    std::sort(A + 1,A + 1 + tot,cmpx);
    cdq(1,tot);
    for(int i = 1;i<=m;++i) printf("%d %d\n",ans1[i],ans2[i]);
    return 0;
}