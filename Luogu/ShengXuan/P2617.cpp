#include <cstdio>
#include <algorithm>
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 1e6 + 100;
int root[maxn],sum[maxn<<6],L[maxn<<6],R[maxn<<6],index;
void modify(int &now,int l,int r,int pos,int val)
{
    if(!now) now = ++index;
    sum[now] += val;
    if(l == r) return;
    int mid = (l + r) >> 1;
    if(pos <= mid) modify(L[now],l,mid,pos,val);
    else modify(R[now],mid + 1,r,pos,val);
}
struct query
{
    int opt,l,r,k,x,y;
}Q[maxn];
int a[maxn];
int n,m;
int H[maxn<<1],tot;
inline int lowbit(const int &x){return x & (-x);}
inline void add(int x,int val)
{
    int t = std::lower_bound(H + 1,H + 1 + tot,a[x]) - H;
    for(;x<=n;x+=lowbit(x)) modify(root[x],1,tot,t,val);
}
int lcnt,rcnt,left[maxn],right[maxn];
int query(int l,int r,int k)
{
    if(l == r) return l;
    int mid = (l + r) >> 1;
    int num = 0;
    for(int i = 1;i<=rcnt;++i) num += sum[L[right[i]]];
    for(int i = 1;i<=lcnt;++i) num -= sum[L[left[i]]];
    if(k <= num)
    {
        for(int i = 1;i<=rcnt;++i) right[i] = L[right[i]];
        for(int i = 1;i<=lcnt;++i) left[i] = L[left[i]];
        return query(l,mid,k);
    }
    else
    {
        for(int i = 1;i<=rcnt;++i) right[i] = R[right[i]];
        for(int i = 1;i<=lcnt;++i) left[i] = R[left[i]];
        return query(mid + 1,r,k-num);
    }
}
inline int ask(int l,int r,int k)
{
    lcnt = rcnt = 0;
    --l;
    while(l)
    {
        left[++lcnt] = root[l];
        l -= lowbit(l);
    }
    while(r)
    {
        right[++rcnt] = root[r];
        r -= lowbit(r);
    }
    return H[query(1,tot,k)];
}
int main()
{
    read(n),read(m);
    for(int i = 1;i<=n;++i) read(a[i]),H[++tot] = a[i];
    for(int i = 1;i<=m;++i)
    {
        char s[5];
        scanf("%s",s + 1);
        if(s[1] == 'Q')
        {
            Q[i].opt = 1;
            read(Q[i].l),read(Q[i].r),read(Q[i].k);
        }
        else
        {
            Q[i].opt = 2;
            read(Q[i].x),read(Q[i].y);
            H[++tot] = Q[i].y;
        }
    }
    std::sort(H + 1,H + 1 + tot);
    tot = std::unique(H + 1,H + 1 + tot) - H - 1;
    for(int i = 1;i<=n;++i) add(i,1);
    for(int i = 1;i<=m;++i)
    {
        if(Q[i].opt == 1)
        {
            printf("%d\n",ask(Q[i].l,Q[i].r,Q[i].k));
        }
        else 
        {
            add(Q[i].x,-1);
            a[Q[i].x] = Q[i].y;
            add(Q[i].x,1);
        }
    }
    return 0;
}