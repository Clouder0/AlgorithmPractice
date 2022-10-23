#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast","-funroll-loops")
#pragma GCC target("ssse3","sse3","sse2","sse","avx2","avx")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#include <cstdio>
#include <cmath>
#include <algorithm>
const int bufSize = 1e5;
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
    for(;c>='0'&&c<='9';c=nc()) r = r * 10 + c - 48;
}
const int maxn = 1e5 + 100;
const int maxm = 1e6 + 100;
int n,m;
int a[maxn];
struct node
{
    int l,r,pos,id,a,b;
    bool operator<(const node &b) const
    {
        if(pos != b.pos) return pos < b.pos;
        if(pos & 1) return r < b.r;
        return r > b.r;
    }
}Q[maxm];
int ANS[maxm];
int cnt[maxn],times[maxn],L[maxn],R[maxn],pos[maxn],maxx;
inline void build()
{
    int size = sqrt(maxx);
    int num = maxx / size;
    for(int i = 1;i<=num;++i)
    {
        L[i] = R[i-1] + 1;
        R[i] = L[i] + size - 1;
        for(int j = L[i];j<=R[i];++j) pos[j] = i;
    }
    if(R[num] < n)
    {
        L[num + 1] = R[num] + 1;
        R[++num] = n;
        for(int j = L[num];j<=n;++j) pos[j] = num;
    }
}
inline void modify(int x,int k)
{
    if(k == 0) return;
    int p = pos[x];
    times[x] += k;
    if(times[x] == k) cnt[p]++;
    else if(times[x] == 0) cnt[p]--;
}
inline int ask(int ll,int rr)
{
    int lp = pos[ll],rp = pos[rr];
    int ans = 0;
    if(lp == rp)
    {
        for(int i = ll;i<=rr;++i) ans += times[i] > 0;
        return ans;
    }
    for(int i = lp + 1;i < rp;++i) ans += cnt[i];
    for(int i = ll;i<=R[lp];++i) ans += times[i] > 0;
    for(int i = L[rp];i<=rr;++i) ans += times[i] > 0;
    return ans;
}
int main()
{
    read(n),read(m);
    for(int i = 1;i<=n;++i) read(a[i]),maxx = std::max(maxx,a[i]);
    build();
    int size = n / sqrt(m);
    for(int i = 1;i<=m;++i) read(Q[i].l),read(Q[i].r),read(Q[i].a),read(Q[i].b),Q[i].pos = Q[i].l / size,Q[i].id = i;
    std::sort(Q + 1,Q + 1 + m);
    int l = 1,r = 0;
    for(int i = 1;i<=m;++i)
    {
        while(l > Q[i].l) modify(a[--l],1);
        while(r < Q[i].r) modify(a[++r],1);
        while(l < Q[i].l) modify(a[l++],-1);
        while(r > Q[i].r) modify(a[r--],-1);
        ANS[Q[i].id] = ask(Q[i].a,Q[i].b);
    }
    for(int i = 1;i<=m;++i) printf("%d\n",ANS[i]);
    return 0;
}