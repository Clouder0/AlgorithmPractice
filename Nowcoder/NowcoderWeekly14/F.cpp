#include <cstdio>
#include <cstring>
#include <queue>
template<typename T>
inline T max(const T &a,const T &b){return a>b?a:b;}
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
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=nc());
}
const int maxn = 2e5 + 100;
namespace Seg
{
    long long maxx[maxn<<5];
    int maxpos[maxn<<5],tim[maxn<<5],root[maxn],L[maxn<<5],R[maxn<<5],tot;
    inline void pushup(int p)
    {
        if (maxx[L[p]] > maxx[R[p]] || (maxx[L[p]] == maxx[R[p]] && tim[L[p]] > tim[R[p]])) tim[p] = tim[L[p]], maxx[p] = maxx[L[p]], maxpos[p] = maxpos[L[p]];
        else tim[p] = tim[R[p]], maxx[p] = maxx[R[p]], maxpos[p] = maxpos[R[p]];            
    }
    void modify(const int &l,const int &r,int &p,const int &pos,const long long &k,const int &t)
    {
        if(!p) p = ++tot,maxpos[p] = maxx[p] = L[p] = R[p] = tim[p] = 0;
        if (l == r) return (void)(maxpos[p] = pos, tim[p] = max(tim[p],t), maxx[p] += k);
        int mid = l + r >> 1;
        if(pos <= mid) modify(l,mid,L[p],pos,k,t);
        else modify(mid + 1,r,R[p],pos,k,t);
        pushup(p);
    }
}
int T,n,m,k;
int A[maxn],B[maxn],C[maxn],ans;
inline void update(int a,int b,int c,int t)
{
    int f = Seg::maxpos[Seg::root[a]];
    Seg::modify(1,n,Seg::root[a],b,c,t);
    int now = Seg::maxpos[Seg::root[a]];
    if(f == now) return;
    if(f) ans += (Seg::maxpos[Seg::root[f]] == a ? 1 : -1);
    if(now) ans += (Seg::maxpos[Seg::root[now]] == a ? -1 : 1);
}
inline void init()
{
    ans = Seg::tot = 0, Seg::tim[0] = 1 << 30;
    for(int i = 1;i<=m;++i) Seg::root[i] = 0;
}
signed main()
{
    read(T);
    while(T--)
    {
        init(),read(n),read(m),read(k);
        for (int i = 1; i <= m; ++i)
        {
            read(A[i]), read(B[i]), read(C[i]);
            update(A[i],B[i],C[i],i),update(B[i],A[i],C[i],i);
            if(i > k) update(A[i - k], B[i - k], -C[i - k], i - k),update(B[i - k], A[i - k], -C[i - k], i - k);
            printf("%d\n", ans);
        }
    }
    return 0;
}