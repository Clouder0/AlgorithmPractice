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
#include <algorithm>
#include <cmath>
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
    r = 0;
    for (c = nc(); !isdigit(c); c = nc());
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r;
}
const int maxn = 2e5 + 100;
const int mod = 1e9 + 7;
inline int add(int x, int y)
{
    int t = x + y;
    return t >= mod ? t - mod : t;
}
inline int mul(int x, int y)
{
    long long t = 1ll * x * y;
    return t < mod ? t : t % mod;
}
int n, m, a[maxn];
int primes[maxn], tot;
bool notprime[maxn];
int invsave[maxn];
inline int inv(int x)
{
    if (invsave[x]) return invsave[x];
    return invsave[x] = mul((mod - mod / x), inv(mod % x));
}
int fastpow(int x, int k)
{
    int res = 1;
    for (; k; k >>= 1)
    {
        if (k & 1) res = mul(res, x);
        x = mul(x, x);
    }
    return res;
}
namespace Seg
{
int L[maxn * 20], R[maxn * 20], maxx[maxn * 20], root[maxn], ind;
void modify(int l, int r, int& p, int pos, int k)
{
    if (!p) p = ++ind;
    maxx[p] = max(maxx[p], k);
    if (l == r) return;
    int mid = l + r >> 1;
    if (pos <= mid) modify(l, mid, L[p], pos, k);
    else modify(mid + 1, r, R[p], pos, k);
}
int ask(int l, int r, int p, int ll, int rr)
{
    if(!p) return 0;
    if (l >= ll && r <= rr) return maxx[p];
    int mid = l + r >> 1, res = 0;
    if (ll <= mid) res = ask(l, mid, L[p], ll, rr);
    if (rr > mid) res = max(res, ask(mid + 1, r, R[p], ll, rr));
    return res;
}
}
namespace Pre
{
int L[maxn * 20], R[maxn * 20], sum[maxn * 20], root[maxn], ind;
inline void pushup(int p) 
{
    if (L[p] && R[p]) sum[p] = mul(sum[L[p]], sum[R[p]]);
    else if (L[p]) sum[p] = sum[L[p]];
    else if (R[p]) sum[p] = sum[R[p]];
    else sum[p] = 1;
}
int modify(int l, int r, int pre, int pos, int k)
{
    int p = ++ind;
    L[p] = L[pre], R[p] = R[pre], sum[p] = sum[pre];
    if (l == r) return (sum[p] == 0 ? sum[p] = k : sum[p] = mul(sum[p], k)), p;
    int mid = l + r >> 1;
    if (pos <= mid) L[p] = modify(l, mid, L[pre], pos, k);
    else R[p] = modify(mid + 1, r, R[pre], pos, k);
    pushup(p);
    return p;
}
int ask(int l, int r, int p, int ll, int rr)
{
    if(!p) return 1;
    if (l >= ll && r <= rr) return sum[p] ? sum[p] : (sum[p] = 1);
    int mid = l + r >> 1, res = 1;
    if (ll <= mid) res = ask(l, mid, L[p], ll, rr);
    if (rr > mid) res = mul(res, ask(mid + 1, r, R[p], ll, rr));
    return res;
}
}  // namespace Pre
int lastvis[maxn];
int main()
{
    read(n);
    invsave[1] = 1;
    int maxx = 0;
    for (int i = 1; i <= n; ++i) read(a[i]), maxx = max(maxx, a[i]);
    int up = std::sqrt(maxx);
    for (int i = 2; i <= up; ++i)
    {
        if (!notprime[i]) primes[++tot] = i;
        for (int j = 1; j <= tot && primes[j] * i <= up; ++j)
        {
            notprime[primes[j] * i] = 1;
            if ((i % primes[j]) == 0) break;
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        int x = a[i];
        for (int j = 1; j <= tot; ++j)
            if((x % primes[j]) == 0)
            {
                int t = 0;
                while ((x % primes[j]) == 0) x /= primes[j], ++t;
                Seg::modify(1, n, Seg::root[j], i, t);
            }
        Pre::root[i] = Pre::root[i - 1];
        if (x != 1)
        {
            if (lastvis[x]) Pre::root[i] = Pre::modify(1, n, Pre::root[i], lastvis[x], inv(x));
            Pre::root[i] = Pre::modify(1, n, Pre::root[i], i, x), lastvis[x] = i;
        }
    }
    int last = 0;
    read(m);
    for (int i = 1, l, r; i <= m; ++i)
    {
        read(l), read(r);
        l = (l + last) % n + 1, r = (r + last) % n + 1;
        if (l > r) std::swap(l, r);
        last = 1;
        for (int j = 1; j <= tot; ++j)
        {
            int t = Seg::ask(1, n, Seg::root[j], l, r);
            if (t) last = mul(last, fastpow(primes[j], t));
        }
        last = mul(last, Pre::ask(1, n, Pre::root[r], l, n));
        printf("%d\n", last);
    }
    return 0;
}