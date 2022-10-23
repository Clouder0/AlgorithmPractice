#include <cstdio>
#include <algorithm>
template<typename T>
inline T max(const T &a,const T &b){return a>b?a:b;}
template<typename T>
void read(T &r)
{
    static char c;static int flag;flag = 1,r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar()) if(c == '-') flag = -1;
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
    r *= flag;
}
const int maxn = 3e5 + 100;
int n;
int A[maxn],B[maxn],C[maxn],X[maxn<<1];
int ansx[maxn<<1],ansy[maxn<<1],cnt;
int maxx[maxn<<3],tag[maxn<<3];
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
int main()
{
    read(n);
    for(int i = 1;i<=n;++i)
        read(A[i]),read(B[i]),read(C[i]),X[i<<1] = B[i],X[(i<<1) - 1] = C[i];
    std::sort(X + 1,X+1+n*2);
    int num = std::unique(X+1,X+1+n*2) - X - 1;
    for(int i = 1;i<=n;++i) 
    {
        int l = std::lower_bound(X + 1,X + 1 + num,B[i]) - X,r = std::lower_bound(X + 1,X + 1 +num,C[i]) - X;
        modify(1,num,1,l,r - 1,A[i]);
    }
    output(1,num,1);
    int last = 0;
    for(int i = 1;i<=num;++i)
    {
        if(h[i] != last)
        {
            ansx[++cnt] = X[i],ansy[cnt] = last;
            ansx[++cnt] = X[i],ansy[cnt] = h[i];
            last = h[i];
        }
    }
    printf("%d\n",cnt);
    for(int i = 1;i<=cnt;++i) printf("%d %d\n",ansx[i],ansy[i]);
    return 0;
}