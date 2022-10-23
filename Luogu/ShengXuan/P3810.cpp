#include <cstdio>
#include <algorithm>
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 2e5 + 100;
struct node
{
    int a,b,c,cnt,ans;
}A[maxn],B[maxn];
int n,maxk,tot;
bool cmp(const node &x,const node &y)
{
    if(x.a != y.a) return x.a < y.a;
    if(x.b != y.b) return x.b < y.b;
    return x.c < y.c;
}
int sum[maxn],vis[maxn],time;
inline void add(int x,int k)
{
    while(x <= maxk) 
    {
        if(vis[x] != time) sum[x] = 0,vis[x] = time;
        sum[x] += k,x += x & -x;
    }
}
inline int ask(int x)
{
    int res = 0;
    while(x)
    {
        if(vis[x] != time) sum[x] = 0,vis[x] = time;
        res += sum[x],x -= x & -x;
    }
    return res;
}
void cdq(int l,int r)
{
    if(l == r) return;
    int mid = l + r >> 1;
    cdq(l,mid),cdq(mid + 1,r);
    int p = l,q = mid + 1,k = l;
    ++time;
    while(p <= mid && q <= r)
    {
        if(A[p].b <= A[q].b)
        {
            add(A[p].c,A[p].cnt);
            B[k++] = A[p++];
        }
        else
        {
            A[q].ans += ask(A[q].c);
            B[k++] = A[q++];
        }
    }
    while(p <= mid) B[k++] = A[p++];
    while(q <= r) A[q].ans += ask(A[q].c),B[k++] = A[q++];
    for(int i = l;i<=r;++i) A[i] = B[i];
}
int d[maxn];
int main()
{
    read(n),read(maxk);
    for(int i = 1;i<=n;++i) read(B[i].a),read(B[i].b),read(B[i].c),B[i].cnt = 1;
    std::sort(B + 1,B + 1 + n,cmp);
    for(int i = 1;i<=n;++i)
    {
        if(B[i].a == B[i+1].a && B[i].b == B[i+1].b && B[i].c == B[i+1].c)
            B[i+1].cnt += B[i].cnt;
        else A[++tot] = B[i];
    }
    cdq(1,tot);
    for(int i = 1;i<=tot;++i) d[A[i].ans + A[i].cnt] += A[i].cnt;
    for(int i = 1;i<=n;++i) printf("%d\n",d[i]);
    return 0;
}