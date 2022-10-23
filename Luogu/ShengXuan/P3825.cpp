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
#include <algorithm>
#include <ctime>
#include <iostream>
#include <random>
using namespace std;
const int maxn = 2e5 + 100;
int n,m,d;
char S[maxn];
int to[maxn], nex[maxn], head[maxn], tot;
inline void add(const int& x, const int& y)
{
    nex[++tot] = head[x], to[tot] = y, head[x] = tot;
}
bool flag;
inline int getf(int x){return x > n ? x - n : x;}
namespace tarjan
{
int dfn[maxn], low[maxn], cnt, ins[maxn], st[maxn], top, sccnum, bel[maxn];
void solve(int u)
{
    if(flag) return;
    dfn[u] = low[u] = ++cnt;
    st[++top] = u, ins[u] = 1;
    for (int p = head[u]; p; p = nex[p])
    {
        if (!dfn[to[p]]) solve(to[p]), low[u] = std::min(low[u], low[to[p]]);
        else if (ins[to[p]]) low[u] = std::min(low[u], dfn[to[p]]);
    }
    if (dfn[u] == low[u])
    {
        ++sccnum;
        while (st[top] != u)
        {
            if (bel[getf(st[top])] == sccnum) { flag = 1; break; }
            bel[st[top]] = sccnum, ins[st[top--]] = 0;
        }
        bel[u] = sccnum, ins[u] = 0, --top;
        if (bel[u + n] == sccnum) flag = 1;
    }
}
}  // namespace tarjan
struct limit
{
    int x,xv,y,yv;
}Q[100010],B[100010];
int bnum;
int pos[10],cnt;
inline int check(int x,int v)
{
    return v == 3 || (S[x] == 3 && v == 2);
}
char out[4][3];
inline void make(int x,int xv,int y,int yv)
{
    if (xv == S[x]) return;
    if (yv == S[y])
    {
        if (check(x, xv)) add(x + n, x);
        else add(x, x + n);
        return;
    }
    //no limitation
    int t1 = check(x, xv), t2 = check(y, yv);
    if (t1 && t2) add(x + n, y + n), add(y, x);
    else if (t1) add(x + n, y), add(y + n, x);
    else if (t2) add(x, y + n), add(y, x + n);
    else add(x, y), add(y + n, x + n);
}
bool issp[maxn];
int oldhead[maxn];
int tester[maxn];
char s1[5],s2[5];
int main()
{
    cin.tie(0),ios::sync_with_stdio(false);
    out[1][1] = 'B',out[1][2] = 'C',out[2][1] = out[3][1] = 'A',out[2][2] = 'C',out[3][2] = 'B';
    srand(time(0) + clock());
    cin >> n >> d >> S + 1 >> m;
    for (int i = 1; i <= m; ++i)
    {
        int x,y;
        cin >> x >> s1 + 1 >> y >> s2 + 1;
        Q[i].x = x, Q[i].y = y, Q[i].xv = s1[1] - 'A' + 1, Q[i].yv = s2[1] - 'A' + 1;
    }
    for (int i = 1; i <= n; ++i) if (S[i] == 'x') pos[++cnt] = i,issp[i] = 1;
    for (int i = 1; i <= n; ++i) S[i] = S[i] - 'a' + 1;
    for (int i = 1; i <= m; ++i) 
    {
        if(!issp[Q[i].x] && !issp[Q[i].y]) make(Q[i].x,Q[i].xv,Q[i].y,Q[i].yv);
        else B[++bnum] = Q[i];
    }
    int oldtot = tot;
    for (int i = 1; i <= 2 * n; ++i) oldhead[i] = head[i];
    for (int i = 0; i < (1 << d); ++i) tester[i] = i;
    int len = 1 << d;
    std::shuffle(tester, tester + (1 << d),rand());
    if (len > 220) len = 220;
    for (int t = 0; t < len; ++t)
    {
        int k = tester[t];
        tot = oldtot;
        for (int i = 1; i <= 2 * n; ++i) head[i] = oldhead[i], tarjan::bel[i] = tarjan::dfn[i] = tarjan::low[i] = 0;
        tarjan::cnt = tarjan::top = tarjan::sccnum = 0;
        for (int i = 1; i <= cnt; ++i)
            if ((1 << (i - 1)) & k) S[pos[i]] = 1;
            else S[pos[i]] = 2;
        //[1,n] choose first,[n + 1,2n] choose second
        for (int i = 1; i <= bnum; ++i) make(B[i].x, B[i].xv, B[i].y, B[i].yv);
        flag = 0;
        for (int i = 1; !flag && i <= 2 * n; ++i) if (!tarjan::dfn[i]) tarjan::solve(i);
        if(flag) goto fail;
        for (int i = 1; i <= n; ++i) 
        {
            if (tarjan::bel[i] < tarjan::bel[i + n]) putchar(out[S[i]][1]);
            else putchar(out[S[i]][2]);
        }
        goto end;
        fail:;
        }
    puts("-1");
    end:;
    return 0;
}
