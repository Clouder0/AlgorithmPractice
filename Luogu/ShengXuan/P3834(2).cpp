#include <cstdio>
#include <algorithm>
#include <ctype.h>
using namespace std;
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
const int maxn = 1e6 + 100;
int n, m, a[maxn], H[maxn], tot, cnt, ans[maxn];
struct node
{
    int type, pos, l, r, val, id;
} Q[maxn],q1[maxn],q2[maxn];
int sum[maxn], vis[maxn], tim;
inline void clear() { ++tim; }
inline void check(int x) { if (vis[x] != tim) sum[x] = 0, vis[x] = tim; }
inline void add(int x, int k)
{
    for (; x <= n; x += x & -x) check(x), sum[x] += k;
}
inline int ask(int x) 
{
    int res =0 ;
    for (; x > 0; x -= x & -x) check(x), res += sum[x];
    return res;
}

void solve(int l, int r, int L, int R)
{
    if(l == r)
    {
        for (int i = L; i <= R; ++i) if(Q[i].type) ans[Q[i].id] = l;
        return;
    }
    int mid = l + r >> 1, cnt1 = 0, cnt2 = 0;
    for (int i = L; i <= R; ++i)
    {
        if(Q[i].type)
        {
            int num = ask(Q[i].r) - ask(Q[i].l - 1);
            if(num >= Q[i].val) q1[++cnt1] = Q[i];
            else Q[i].val -= num, q2[++cnt2] = Q[i];
        }
        else
        {
            if (Q[i].val <= mid) add(Q[i].pos, 1), q1[++cnt1] = Q[i];
            else q2[++cnt2] = Q[i];
        }
    }
    clear();
    for (int i = 1; i <= cnt1; ++i) Q[L + i - 1] = q1[i];
    for (int i = 1; i <= cnt2; ++i) Q[L + cnt1 + i - 1] = q2[i];
    solve(l, mid, L, L + cnt1 - 1), solve(mid + 1, r, L + cnt1, R);
}
signed main()
{
    read(n), read(m);
    for (int i = 1; i <= n; ++i) read(a[i]), H[++tot] = a[i];
    sort(H + 1, H + 1 + tot), tot = unique(H + 1, H + 1 + tot) - H - 1;
    for (int i = 1; i <= n; ++i) a[i] = lower_bound(H + 1, H + 1 + tot, a[i]) - H;
    for (int i = 1; i <= n; ++i) Q[++cnt].type = 0, Q[cnt].pos = i, Q[cnt].val = a[i];
    for (int i = 1; i <= m; ++i) read(Q[++cnt].l), read(Q[cnt].r), read(Q[cnt].val), Q[cnt].id = i, Q[cnt].type = 1;
    solve(1, tot, 1, cnt);
    for (int i = 1; i <= m; ++i) printf("%d\n", H[ans[i]]);
    return 0;
}