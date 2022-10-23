#include <cstdio>
#include <algorithm>
template<typename T>
inline T max(const T &a,const T &b){return a>b?a:b;}
template<typename T>
inline T min(const T &a,const T &b){return a<b?a:b;}
const int bufSize = 5e6;
inline char nc()
{
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
template <typename T>
void read(T &r)
{
    static char c; r = 0;
    for (c = nc(); c > '9' || c < '0'; c = nc());
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = nc());
}
const int maxn = 4e6 + 100;
int n;
struct query
{
    int opt, t, x, y;
} Q[maxn];
int H[maxn], tot;
namespace seg
{
    #define ls p<<1
    #define rs p<<1|1
    long long presum[maxn<<1],sufsum[maxn<<1],premid[maxn<<1],sufmid[maxn<<1];
    void modifypre(int l,int r,int p,int pos,int k)
    {
        presum[p] += k;
        int mid = l + r >> 1;
        if(mid == pos) premid[p] += k;
        else if(pos < mid) modifypre(l,mid-1,ls,pos,k);
        else modifypre(mid + 1,r,rs,pos,k);
    }
    void modifysuf(int l, int r, int p, int pos, int k)
    {
        sufsum[p] += k;
        int mid = l + r >> 1;
        if(mid == pos) sufmid[p] += k;
        else if(pos < mid) modifysuf(l,mid-1,ls,pos,k);
        else modifysuf(mid + 1,r,rs,pos,k);
    }
    long long askAns(int l,int r,int p,long long ps,long long ss)
    {
        if(l > r) return -(1ll<<60);
        int mid = l + r >> 1;
        long long tps = ps + presum[ls] + premid[p];
        long long tss = ss + sufsum[rs] + sufmid[p];
        long long ans = min(tps,tss);
        if(tps > tss) return max(ans,askAns(l,mid - 1,ls,ps,tss));
        else return max(ans,askAns(mid + 1,r,rs,tps,ss));
    }
    int askPos(int l,int r,int p,long long ps,long long ss,long long v)
    {
        if(l > r) return 0;
        int mid = l + r >> 1;
        long long tps = ps + presum[ls] + premid[p];
        long long tss = ss + sufsum[rs] + sufmid[p];
        long long ans = min(tps,tss);
        if(ans == v) return max(mid,askPos(mid + 1,r,rs,tps,ss,v));
        if(tps > tss) return askPos(l,mid - 1,ls,ps,tss,v);
        else return askPos(mid + 1,r,rs,tps,ss,v);
    }
}
int main()
{
    read(n);
    for (int i = 1; i <= n; ++i)
    {
        read(Q[i].opt);
        if (Q[i].opt == 1) read(Q[i].t), read(Q[i].x), read(Q[i].y), H[++tot] = Q[i].x;
        else read(Q[i].t);
    }
    std::sort(H + 1, H + 1 + tot);
    tot = std::unique(H + 1, H + 1 + tot) - H - 1;
    for (int i = 1; i <= n; ++i)
    {
        if (Q[i].opt == 1)
        {
            int x = std::lower_bound(H + 1, H + 1 + tot, Q[i].x) - H;
            if (Q[i].t == 0) seg::modifypre(1,tot,1,x,Q[i].y);
            else seg::modifysuf(1,tot,1,x,Q[i].y);
        }
        else
        {
            int p = Q[i].t;
            int x = std::lower_bound(H + 1, H + 1 + tot, Q[p].x) - H;
            if (Q[p].t == 0) seg::modifypre(1,tot,1,x,-Q[p].y);
            else seg::modifysuf(1,tot,1,x,-Q[p].y);
        }
        long long res = seg::askAns(1,tot,1,0,0);
        if(res == 0) puts("Peace");
        else printf("%d %lld\n",H[seg::askPos(1,tot,1,0,0,res)],res * 2);
    }
    return 0;
}