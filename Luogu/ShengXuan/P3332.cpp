#include <cstdio>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
#define int long long
#define DEBUG
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
const int maxn = 5e4 + 100;
int n, m, ans[maxn];
struct node
{
    int type, l, r, val, id;
} Q[maxn], q1[maxn], q2[maxn];
namespace Bit
{
int sum1[maxn], sum2[maxn], vis[maxn], tim;
inline void clear(){++tim;}
inline void check(int x) { if (vis[x] != tim) vis[x] = tim, sum1[x] = sum2[x] = 0; }
inline void add(int x, int k)
{
    int tmp = k * x;
    for (; x <= n; x += x & -x) check(x),sum1[x] += k, sum2[x] += tmp;
}
inline int ask(int x)
{
    int t = x, res1 = 0, res2 = 0;
    for (; x > 0; x -= x & -x) check(x), res1 += sum1[x], res2 += sum2[x];
    return (t + 1) * res1 - res2;
}
inline void addrange(int l, int r, int k) { add(l, k), add(r + 1, -k); }
inline int askrange(int l, int r) { return ask(r) - ask(l - 1); }
}  // namespace Bit
void solve(int l, int r, int L, int R)
{
    if (L > R) return;
    if (l == r)
    {
        for (int i = L; i <= R; ++i) ans[Q[i].id] = l;
        return;
    }
    int mid = l + ((r - l) >> 1), cnt1 = 0, cnt2 = 0;
    for (int i = L; i <= R; ++i)
    {
        if (Q[i].type == 1)
        {
            if (Q[i].val > mid) Bit::addrange(Q[i].l, Q[i].r, 1),q2[++cnt2] = Q[i];
            else q1[++cnt1] = Q[i];
        }
        else
        {
            int num = Bit::askrange(Q[i].l,Q[i].r);
            if (num >= Q[i].val) q2[++cnt2] = Q[i];
            else Q[i].val -= num, q1[++cnt1] = Q[i];
        }
    }
    Bit::clear();
    for (int i = 1; i <= cnt1; ++i) Q[L + i - 1] = q1[i];
    for (int i = 1; i <= cnt2; ++i) Q[L + cnt1 + i - 1] = q2[i];
    solve(l, mid, L, L + cnt1 - 1), solve(mid + 1, r, L + cnt1, R);
}
signed main()
{
    read(n), read(m);
    int qnum = 0;
    for (int i = 1; i <= m; ++i) 
    {
        read(Q[i].type), read(Q[i].l), read(Q[i].r), read(Q[i].val);
        if (Q[i].type == 2) Q[i].id = ++qnum;
    }
    solve(-n, n, 1, m);
    for (int i = 1; i <= qnum; ++i) printf("%lld\n", ans[i]);
    return 0;
}