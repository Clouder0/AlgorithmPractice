#pragma optimize(O2)
#include <cstdio>
using namespace std;
inline char nc()
{
    static char buf[1000000],*p1 = buf,*p2 = buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
}
template<typename T>
void read(T &r)
{
    static char c;static int flag;flag = 1,r=0;
    for(c=nc();c>'9'||c<'0';c=nc()) if(c == '-')  flag = -1;
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=nc());r *= flag;
}
template<typename T>
inline T min(const T &a,const T &b){return a<b?a:b;}
template<typename T>
inline T max(const T &a,const T &b){return a>b?a:b;}
int n,k;
const int maxn = 1e6 + 10;
int minn[maxn<<2],maxx[maxn<<2];
inline void push_up(const int &p)
{
    minn[p] = min(minn[p<<1],minn[p<<1|1]);
    maxx[p] = max(maxx[p<<1],maxx[p<<1|1]);
}
inline void build(const int &l,const int &r,const int &p)
{
    if(l == r)
    {
        int temp;
        read(temp);
        minn[p] = maxx[p] = temp;
        return;
    }
    int mid = (l+r)>>1;
    build(l,mid,p<<1);
    build(mid+1,r,p<<1|1);
    push_up(p);
}
struct ans
{
    int minn,maxx;
    ans(){}
    ans(const int &_minn,const int &_maxx) : minn(_minn),maxx(_maxx){}
};
int ll,rr;
inline ans ask(const int &l,const int &r,const int &p)
{
    if(l >= ll && r <= rr)
        return ans(minn[p],maxx[p]);
    int mid = (l+r)>>1;
    ans a;
    bool flag = false;
    if(ll <= mid)
        a = ask(l,mid,p<<1),flag = true;
    if(rr > mid)
    {
        if(flag)
        {
            ans b = ask(mid+1,r,p<<1|1);
            a.minn = min(a.minn,b.minn);
            a.maxx = max(a.maxx,b.maxx);
        }
        else
            a = ask(mid+1,r,p<<1|1);
    }
    return a;
}
ans aa[maxn];
int main()
{
    read(n);
    read(k);
    build(1,n,1);
    ans a;
    for(int i = 1;i+k-1<=n;++i)
    {
        ll = i;
        rr = i + k - 1;
        aa[i] = ask(1,n,1);
    }
    for(int i = 1;i+k-1<=n;++i)
        printf("%d ",aa[i].minn);
    putchar('\n');
    for(int i = 1;i+k-1<=n;++i)
        printf("%d ",aa[i].maxx);
    return 0;
}