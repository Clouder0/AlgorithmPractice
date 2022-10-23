#include <cstdio>
#include <algorithm>
#include <ctype.h>
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
const int maxn = 2e5 + 100;
const int mod = 998244353;
int n, to[maxn], f[maxn][2];
struct node
{
    int pos, d;
} A[maxn];
bool cmp(const node& a, const node& b) { return a.pos < b.pos; }
int maxx[maxn << 2];
#define ls p << 1
#define rs p << 1 | 1
inline void pushup(int p) { maxx[p] = std::max(maxx[ls], maxx[rs]); }
void modify(int l, int r, int p, int pos, int k)
{
    if(l == r) return (void)(maxx[p] = k);
    int mid = l + r >> 1;
    if (pos <= mid) modify(l, mid, ls, pos, k);
    else modify(mid + 1, r, rs, pos, k);
    pushup(p);
}
int ask(int l, int r, int p, int ll, int rr)
{
    if (ll > rr) return 0;
    if (l >= ll && r <= rr) return maxx[p];
    int mid = l + r >> 1, res = 0;
    if (ll <= mid) res = ask(l, mid, ls, ll, rr);
    if (rr > mid) res = std::max(res, ask(mid + 1, r, rs, ll, rr));
    return res;
}
int main()
{
    read(n);
    for (int i = 1; i <= n; ++i) read(A[i].pos), read(A[i].d);
    std::sort(A + 1, A + 1 + n, cmp);
    for (int i = n; i; --i)
    {
        int l = i, r = n, mid, ans = 0;
        while (l <= r)
        {
            mid = l + r >> 1;
            if (A[mid].pos < A[i].pos + A[i].d) ans = mid, l = mid + 1;
            else r = mid - 1;
        }
        to[i] = std::max(r + 1, ask(1, n, 1, i + 1, ans));
        modify(1, n, 1, i, to[i]);
    }
    f[n + 1][0] = 1;
    for (int i = n; i; --i)
    {
        f[i][0] = (f[i + 1][0] + f[i + 1][1]) % mod;
        f[i][1] = (f[to[i]][0] + f[to[i]][1]) % mod;
    }
    printf("%d\n", (f[1][0] + f[1][1]) % mod);
    return 0;
}