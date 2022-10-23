#include <cstdio>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
#define ls p << 1
#define rs p << 1 | 1
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
const int maxn = 1e5 + 100;
int n, a[maxn], last[maxn], minn[maxn << 2], can[maxn];
inline void pushup(int p) { minn[p] = std::min(minn[ls], minn[rs]); }
void modify(int l, int r, int p, int pos, int k)
{
    if (l == r) return (void)(minn[p] = k);
    int mid = l + r >> 1;
    if (pos <= mid) modify(l, mid, ls, pos, k);
    else modify(mid + 1, r, rs, pos, k);
    pushup(p);
}
int ask(int l, int r, int p, int ll, int rr)
{
    if(ll > rr) return 0;
    if(l >= ll && r <= rr) return minn[p];
    int mid = l + r >> 1,res = n + 1;
    if (ll <= mid) res = ask(l, mid, ls, ll, rr);
    if (rr > mid) res = std::min(res, ask(mid + 1, r, rs, ll, rr));
    return res;
}
int main()
{
    read(n);
    for (int i = 1; i <= n; ++i) read(a[i]), can[1] |= (a[i] != 1);
    for (int i = 1; i <= n; ++i)
    {
        if (ask(1, n, 1, 1, a[i] - 1) > last[a[i]]) can[a[i]] = 1;
        modify(1, n, 1, a[i], last[a[i]] = i);
    }
    for (int i = 2; i <= n + 1; ++i)
        if (ask(1, n, 1, 1, i - 1) > last[i]) can[i] = 1;
    int mex = 1;
    while (can[mex] && mex < n + 2) ++mex;
    printf("%d\n", mex);
    return 0;
}