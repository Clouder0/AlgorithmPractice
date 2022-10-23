#include <cstdio>
template<typename T>
void read(T &r)
{
    static char c;static int flag;flag = 1,r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar()) if(c == '-') flag = -1;
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
    r *= flag;
}
const int maxn = 2e6 + 100;
struct node
{
    int type,pos,val;
}a[maxn],tmp[maxn];
int n,m,tot;
long long ans[maxn],qt;
void cdq(int l,int r)
{
    if(l == r) return;
    int mid = l + r >> 1;
    cdq(l,mid),cdq(mid + 1,r);
    int k = l,p = l, q = mid + 1;
    long long sum = 0;
    while(p <= mid && q <= r)
    {
        if(a[p].pos <= a[q].pos)
        {
            if(a[p].type == 2) sum += a[p].val;
            tmp[k++] = a[p++];
        }
        else
        {
            if(a[q].type != 2) ans[a[q].val] += a[q].type * sum;
            tmp[k++] = a[q++];
        }
    }
    while(p <= mid) tmp[k++] = a[p++];
    while(q <= r) 
    {
        if(a[q].type != 2) ans[a[q].val] += a[q].type * sum;
        tmp[k++] = a[q++];
    }
    for(int i = l;i<=r;++i) a[i] = tmp[i];
}
int main()
{
    read(n),read(m);
    for(int i = 1;i<=n;++i)
    {
        int x;
        read(x);
        a[++tot].pos = i;
        a[tot].type = 2,a[tot].val = x;
    }
    for(int i = 1;i<=m;++i)
    {
        int opt,x,y;
        read(opt),read(x),read(y);
        if(opt == 1)
        {
            a[++tot].pos = x;
            a[tot].type = 2,a[tot].val = y;
        }
        else
        {
            a[++tot].pos = x - 1,a[tot].type = -1,a[tot].val = ++qt;
            a[++tot].pos = y,a[tot].type = 1,a[tot].val = qt;
        }
    }
    cdq(1,tot);
    for(int i = 1;i<=qt;++i) printf("%lld\n",ans[i]);
    return 0;
}