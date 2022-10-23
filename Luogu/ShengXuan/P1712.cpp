#include <cstdio>
#include <algorithm>
#include <ctype.h>
using std::max;
const int bufSize = 1e6;
inline char nc()
{
    #ifdef DEBUG
    return getchar();
    #endif
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
template<typename T>
inline T read(T &r)
{
    static char c;
    static int flag;
    flag = 1, r = 0;
    for (c = nc(); !isdigit(c); c = nc()) if (c == '-') flag = -1;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r *= flag;
}
const int maxn = 2e6 + 100;
int n, m;
struct node
{
    int l,r;
}A[maxn];
bool cmp(const node &a,const node &b) { return (a.r - a.l) < (b.r - b.l); }
int H[maxn], cnt;
#define ls p << 1
#define rs p << 1 | 1
int maxx[maxn << 2], tag[maxn << 2];
inline void pushup(int p) { maxx[p] = max(maxx[ls], maxx[rs]); }
inline void pushdown(int p)
{
    if(!tag[p]) return;
    maxx[ls] += tag[p],maxx[rs] += tag[p],tag[ls] += tag[p],tag[rs] += tag[p];
    tag[p] = 0;
}
void modify(int l,int r,int p,int ll,int rr,int k)
{
    if(l >= ll && r<= rr) return (void)(tag[p] += k,maxx[p] += k);
    int mid = l + r >> 1;
    pushdown(p);
    if(ll <= mid) modify(l,mid,ls,ll,rr,k);
    if(rr > mid) modify(mid + 1,r,rs,ll,rr,k);
    pushup(p);
}
int main()
{
    read(n), read(m);
    for (int i = 1; i <= n; ++i) read(A[i].l), read(A[i].r), H[++cnt] = A[i].l - 1,H[++cnt] = A[i].l, H[++cnt] = A[i].r,H[++cnt] = A[i].r + 1;
    std::sort(A + 1, A + 1 + n,cmp);
    std::sort(H + 1,H + 1 + cnt),cnt = std::unique(H + 1,H + 1 + cnt) - H - 1;
    for (int i = 1; i <= n; ++i) 
    {
        A[i].l = std::lower_bound(H + 1, H + 1 + cnt, A[i].l) - H;
        A[i].r = std::lower_bound(H + 1, H + 1 + cnt, A[i].r) - H;
    }
    int l = 1, r = 0, ans = 1 << 30;
    while(l <= n)
    {
        while(maxx[1] < m && r < n) ++r, modify(1, cnt, 1, A[r].l, A[r].r, 1);
        if(maxx[1] >= m) ans = std::min(ans,H[A[r].r] - H[A[r].l] - H[A[l].r] + H[A[l].l]);
        modify(1, cnt, 1, A[l].l, A[l].r, -1), ++l;
    }
    if (ans == (1 << 30)) puts("-1");
    else printf("%d\n", ans);
    return 0;
}