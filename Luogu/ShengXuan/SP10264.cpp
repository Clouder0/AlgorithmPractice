#include <cstdio>
#include <algorithm>
#include <vector>
#include <ctype.h>
using std::min;
using std::vector;
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
const int maxn = 3e5 + 100;
int n, m, k, ans[maxn];
vector<int> V[maxn];
struct node
{
    int l, r, x;
} A[maxn];
struct node2
{
    int id, need;
} B[maxn], q1[maxn], q2[maxn];
int vis[maxn],tim;
long long sum[maxn];
inline void clear(){++tim;}
inline void check(int x) { if (vis[x] != tim) vis[x] = tim, sum[x] = 0; }
const int inf = 1e9 + 100;
inline long long plus(long long a, long long b) { return min(a + b, 1ll * inf); }
inline void add(int x, int k)
{
    for (; x <= m; x += x & -x) check(x), sum[x] += k;
}
inline void addrange(int l, int r, int k) { add(l, k), add(r + 1, -k); }
inline long long ask(int x)
{
    long long res = 0;
    for (; x > 0; x -= x & -x) check(x), res = plus(res, sum[x]);
    return res;
}
void solve(int l, int r, int L, int R)
{
    if(L > R) return;
    if(l == r) 
    {
        for (int i = L; i <= R; ++i) ans[B[i].id] = l;
        return;
    }
    int mid = l + r >> 1, cnt1 = 0, cnt2 = 0;
    for (int i = l; i <= mid; ++i)
    {
        if (A[i].l <= A[i].r) addrange(A[i].l, A[i].r, A[i].x);
        else addrange(A[i].l, m, A[i].x), addrange(1, A[i].r, A[i].x);
    }
    for (int i = L; i <= R; ++i)
    {
        long long t = 0;
        for (vector<int>::iterator it = V[B[i].id].begin(); it != V[B[i].id].end(); ++it) t = plus(t, ask(*it));
        if (t >= B[i].need) q1[++cnt1] = B[i];
        else B[i].need -= t, q2[++cnt2] = B[i];
    }
    clear();
    for (int i = 1; i <= cnt1; ++i) B[L + i - 1] = q1[i];
    for (int i = 1; i <= cnt2; ++i) B[L + cnt1 + i - 1] = q2[i];
    solve(l, mid, L, L + cnt1 - 1), solve(mid + 1, r, L + cnt1, R);
}
signed main()
{
    read(n),read(m);
    for (int i = 1, x; i <= m; ++i) read(x), V[x].push_back(i);
    for (int i = 1; i <= n; ++i) read(B[i].need), B[i].id = i;
    read(k);
    for (int i = 1; i <= k; ++i) read(A[i].l), read(A[i].r), read(A[i].x);
    A[k + 1].l = 1, A[k + 1].r = n, A[k + 1].x = inf;
    solve(1, k + 1, 1, n);
    for (int i = 1; i <= n; ++i) if (ans[i] <= k) printf("%d\n", ans[i]); else puts("NIE");
    return 0;
}