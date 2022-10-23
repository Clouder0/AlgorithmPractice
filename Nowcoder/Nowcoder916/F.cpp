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
#include <ctype.h>
#define int long long
const int bufSize = 1e7;
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
const int maxn = 1e6 + 10;
int n, p, a[maxn], b[maxn], need[maxn];
inline void exgcd(int a, int b, int& x, int& y)
{
    if (b == 0) return (void)(x = 1, y = 0);
    exgcd(b, a % b, y, x), y -= (a / b) * x;
}
int get(int x, int n, int mod)
{
    // kx = n (mod mod)
    // kx + m * mod = n
    // get min k
    int k, m;
    // p is prime, g is 1
    exgcd(x, mod, k, m);
    k *= n, m *= n;
    k = ((k % mod) + mod) % mod;
    return k;
}
signed main()
{
    read(n), read(p);
    for (int i = 1; i <= n; ++i) read(a[i]), a[i] %= p;
    for (int i = 1; i <= n; ++i) read(b[i]);

    int flag = 1;
    for (int i = 1; flag && i <= n; ++i) if(a[i] != b[i]) flag = 0;
    if(flag)
    {
        puts("0");
        return 0;
    }

    for (int i = 1; i <= n; ++i) 
    {
        if (b[i] - a[i] < 0)
            ++need[b[i] - a[i] + p];
        else
            ++need[b[i] - a[i]];
    }
    long long minn = 1ll << 60;
    int nx = 0;
    for (int x = 1; x < p; ++x)
    {
        long long now = 0;
        long long inv = get(x, 1, p);
        for (int i = 1; i < p; ++i)
        {
            if (!need[i]) continue;
            int times = (inv * i) % p;
//            if(x == 4) printf("i:%d times %d\n",i,times);
            now = std::max(now, times);
            if (now > minn) goto no;
        }
//        printf("x %d %lld\n",x,now);
        if (now < minn) minn = now, nx = x;
    no:;
    }
//    printf("%lld\n",minn);
    printf("%lld\n", nx);
    return 0;
}