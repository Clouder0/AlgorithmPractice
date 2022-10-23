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
#include <vector>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
using namespace std;
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
const int maxn = 4e6 + 100;;
int n, m;
int a[maxn],b[maxn],c[maxn],d[maxn];
int T[maxn],tt;
int uptag[maxn],righttag[maxn];
vector<int> del[maxn];
const int inf = 1<<30;
int tag[maxn << 2],maxx[maxn << 2],maxid[maxn << 2];
#define ls p<<1
#define rs p<<1|1
inline void pushup(int p)
{
    maxx[p] = max(maxx[ls], maxx[rs]);
    if(maxx[p] == maxx[ls]) maxid[p] = maxid[ls];
    else maxid[p] = maxid[rs];
}
void build(int l, int r, int p)
{
    if(l == r) return (void)(maxx[p] = righttag[l],maxid[p] = l);
    int mid = l + r >> 1;
    build(l,mid,ls),build(mid + 1,r,rs),pushup(p);
}
inline void pushdown(int p)
{
    if(!tag[p]) return;
    maxx[ls] += tag[p],maxx[rs] += tag[p];
    tag[ls] += tag[p],tag[rs] += tag[p];
    tag[p] = 0;
}
void modify(int l,int r,int p,int ll,int rr,int k)
{
    if(ll > rr) return;
    if(l >= ll && r <= rr) return (void)(maxx[p] += k,tag[p] += k);
    pushdown(p);
    int mid = l + r >> 1;
    if(ll <= mid) modify(l,mid,ls,ll,rr,k);
    if(rr > mid) modify(mid + 1,r,rs,ll,rr,k);
    pushup(p);
}
int ask(int l,int r,int p,int k)
{
    if(maxx[p] < k) return tt + 1;
    if(maxx[p] == k) return maxid[p];
    pushdown(p);
    int mid = l + r >> 1;
    int lans = ask(l,mid,ls,k);
    if(lans <= tt)  return lans;
    int rans = ask(mid + 1,r,rs,k);
    if(rans <= tt) return rans;
}
int premax[maxn],premaxid[maxn],tmp[maxn];
int main()
{
    read(n),read(m);
    for (int i = 1; i <= n; ++i) read(a[i]), read(b[i]);
    for (int i = 1; i <= m; ++i) read(c[i]), read(d[i]);
    T[++tt] = 0;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            int up = c[j] - a[i] + 1;
            int right = d[j] - b[i] + 1;
            if(up > 0) T[++tt] = up;
            if(right > 0) T[++tt] = right;
        }
    }
    sort(T + 1,T + 1 + tt),tt = unique(T + 1,T + 1 + tt) - T - 1;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            int up = lower_bound(T + 1,T + 1 + tt,c[j] - a[i] + 1) - T;
            int right = lower_bound(T + 1,T + 1 + tt,d[j] - b[i] + 1) - T;
            uptag[up]++,righttag[right]++;
            del[up].push_back(right);
        }
    }
    for (int i = 1; i <= tt; ++i) uptag[i] += uptag[i - 1];
    for (int i = 1; i <= tt; ++i) righttag[i] += righttag[i - 1];
    for (int i = 1; i <= tt; ++i) 
    {
        premax[i] = premax[i-1];
        if(righttag[i]  > premax[i]) premaxid[i] = i,premax[i] = righttag[i];
    }
    build(1,tt,1);
    int ans = 1 << 30;
    for (int i = 1; i <= tt; ++i)
    {
        int maxx = 0,maxid = 0,num = 0;
        for (vector<int>::iterator it = del[i].begin(); it != del[i].end(); ++it) tmp[*it]--;
        for(vector<int>::reverse_iterator rit = del[i].rbegin();rit!=del[i].rend();++rit)
        {
            ++num;
            if() ans = min(ans,T[i] + T[premax[]]);
        }
        for (vector<int>::iterator it = del[i].begin(); it != del[i].end(); ++it) tmp[*it]++;
        int need = n * m - uptag[i];
        if(maxx[1] == need) ans = min(ans,T[i] + T[maxid[1]]);
    }
    printf("%d\n",ans);
    return 0;
}