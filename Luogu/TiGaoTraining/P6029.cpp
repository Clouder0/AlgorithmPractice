#include <cstdio>
#include <cmath>
template<typename T>
inline T min(const T &a,const T &b){return a<b?a:b;}
template<typename T>
inline T max(const T &a,const T &b){return a>b?a:b;}
const int bufSize = 1000000;
inline char nc()
{
    static char buf[bufSize],*p1 = buf,*p2 = buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,bufSize,stdin),p1==p2)?EOF:*p1++;
}
template<typename T>
void read(T &r)
{
    static char c;static int flag;flag = 1,r=0;
    for(c=nc();c>'9'||c<'0';c=nc()) if(c=='-') flag = -1;
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=nc());
    r *= flag;
}
const int maxn = 2e5 + 100;
int n,m;
int add[maxn<<2],maxx[maxn<<2],minn[maxn<<2];
long long sum[maxn<<2];
inline void pushdown(const int &l,const int &r,const int &p)
{
    if(add[p] == 0)
        return;
    int mid = l + r >> 1;
    int ls = p<<1,rs = p<<1|1;
    sum[ls] += (long long)(mid - l + 1) * add[p];
    sum[rs] += (long long)(r - mid) * add[p];
    maxx[ls] += add[p],minn[ls] += add[p];
    maxx[rs] += add[p],minn[rs] += add[p];
    add[ls] += add[p],add[rs] += add[p];
    add[p] = 0;
}
inline void pushup(const int &p)
{
    sum[p] = sum[p<<1] + sum[p<<1|1];
    maxx[p] = max(maxx[p<<1],maxx[p<<1|1]);
    minn[p] = min(minn[p<<1],minn[p<<1|1]);
}
int ll,rr,k;
void addSum(const int &l,const int &r,const int &p)
{
    if(ll <= l && rr >= r)
    {
        sum[p] += (long long)(r - l + 1) * k;
        add[p] += k;
        maxx[p] += k,minn[p] += k;
        return;
    }
    pushdown(l,r,p);
    int mid = l + r >> 1;
    if(ll <= mid)
        addSum(l,mid,p<<1);
    if(rr > mid)
        addSum(mid + 1,r,p<<1|1);
    pushup(p);
}
void multiDiv(const int &l,const int &r,const int &p)
{
    pushdown(l,r,p);
    int mid = l + r >> 1;
    if(ll <= l && rr >= r)
    {
        int a,b;
        if(maxx[p] < 0) a = maxx[p] - ((maxx[p] - k + 1) / k);
        else a = maxx[p] - (maxx[p] / k);
        if(minn[p] < 0) b = minn[p] - ((minn[p] - k + 1) / k);
        else b = minn[p] - (minn[p] / k);
        if(a == b)
        {
            sum[p] += (r-l+1) * (-a);
            add[p] -= a;
            maxx[p] -= a,minn[p] -= a;
            return;
        }
        multiDiv(l,mid,p<<1);
        multiDiv(mid + 1,r,p<<1|1);
        pushup(p);
        return;
    }
    if(ll <= mid)
        multiDiv(l,mid,p<<1);
    if(rr > mid)
        multiDiv(mid + 1,r,p<<1|1);
    pushup(p);
}
int multiMin(const int &l,const int &r,const int &p)
{
    if(ll <= l && rr >= r)
        return minn[p];
    int mid = l + r >> 1;
    int ans = 1 << 30;
    pushdown(l,r,p);
    if(ll <= mid)
        ans = multiMin(l,mid,p<<1);
    if(rr > mid)
        ans = min(ans,multiMin(mid + 1,r,p<<1|1));
    return ans;
}
long long askSum(const int &l,const int &r,const int &p)
{
    if(ll <= l && rr >= r)
        return sum[p];
    int mid = l + r >> 1;
    long long ans = 0;
    pushdown(l,r,p);
    if(ll <= mid)
        ans = askSum(l,mid,p<<1);
    if(rr > mid)
        ans += askSum(mid + 1,r,p<<1|1);
    return ans;
}
void build(const int &l,const int &r,const int &p)
{
    if(l == r)
    {
        read(sum[p]);
        maxx[p] = minn[p] = sum[p];
        return;
    }
    int mid = l + r >> 1;
    build(l,mid,p<<1);
    build(mid + 1,r,p<<1|1);
    pushup(p);
}
int main()
{
    read(n);
    read(m);
    build(1,n,1);
    while(m--)
    {
        int opt;
        read(opt);
        read(ll),read(rr);
        ++ll,++rr;
        if(opt == 1)
        {
            read(k);
            addSum(1,n,1);
        }
        else if(opt == 2)
        {
            read(k);
            multiDiv(1,n,1);
        }
        else if(opt == 3)
        {
            printf("%d\n",multiMin(1,n,1));
        }
        else
            printf("%lld\n",askSum(1,n,1));
    }
    return 0;
}