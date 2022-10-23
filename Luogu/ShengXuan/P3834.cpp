#include <cstdio>
#include <algorithm>
template<typename T>
void read(T &r)
{
    static char c;static int flag;flag = 1,r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar()) if(c == '-') flag = -1;
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
    r *= flag;
}
const int maxn = 2e6 + 100;
int n,m;
int H[maxn],origin[maxn];
namespace Tree
{
    int root[maxn],sum[maxn<<4],L[maxn<<4],R[maxn<<4],index;
    inline void pushup(const int &p) {sum[p] = sum[L[p]] + sum[R[p]];}
    int modify(int l,int r,int p,int pos)
    {
        int now = ++index;
        L[now] = L[p],R[now] = R[p],sum[now] = sum[p];
        if(l == r)
        {
            sum[now]++;
            return now;
        }
        int mid = l + r >> 1;
        if(pos <= mid) L[now] = modify(l,mid,L[p],pos);
        if(pos > mid) R[now] = modify(mid + 1,r,R[p],pos);
        pushup(now);
        return now;
    }
    int query(int l,int r,int pl,int pr,int k)
    {
        if(l == r) return l;
        int mid = l + r >> 1;
        int num = sum[L[pr]] - sum[L[pl]];
        if(k <= num) return query(l,mid,L[pl],L[pr],k);
        else return query(mid + 1,r,R[pl],R[pr],k - num);
    }
    int build(int l,int r)
    {
        int now = ++index;
        if(l == r) return now;
        int mid = l + r >> 1;
        L[now] = build(l,mid);
        R[now] = build(mid + 1,r);
        return now;
    }
}
int main()
{
    read(n),read(m);
    for(int i = 1;i<=n;++i) read(origin[i]),H[i] = origin[i];
    std::sort(H + 1,H + 1 + n);
    int tot = std::unique(H + 1,H + 1 + n) - H - 1;
    Tree::root[0] = Tree::build(1,tot);
    for(int i = 1;i<=n;++i)
    {
        int t = std::lower_bound(H + 1,H + 1 + tot,origin[i]) - H;
        Tree::root[i] = Tree::modify(1,tot,Tree::root[i-1],t);
    }
    while(m--)
    {
        int a,b,c;
        read(a),read(b),read(c);
        printf("%d\n",H[Tree::query(1,tot,Tree::root[a - 1],Tree::root[b],c)]);
    }
    return 0;
}