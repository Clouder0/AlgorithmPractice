#include <algorithm>
#include <cstdio>
#include <ctype.h>
const int bufSize = 1e6;
using namespace std;
//#define DEBUG
inline char nc()
{
#ifdef DEBUG
    return getchar();
#endif
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
template <typename T>
inline T read(T& r)
{
    static char c;
    static int flag;
    flag = 1, r = 0;
    for (c = nc(); !isdigit(c); c = nc()) if (c == '-') flag = -1;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r *= flag;
}
const int maxn = 2e5 + 100;
int n, m, L;
int pre[maxn], nex[maxn], pos[maxn], limit[maxn];
struct node
{
    int pos, id, direction, near, neardis;
} A[maxn];
inline bool cmp(const node& a, const node& b) { return a.pos < b.pos; }
const int inf = 1 << 30;
struct segtree
{
    int minn[maxn << 2], minid[maxn << 2], exitid[maxn << 2], addtag[maxn << 2], exittag[maxn << 2];
#define ls p << 1
#define rs p << 1 | 1
    inline void pushup(int p)
    {
        if (minn[ls] < minn[rs] || (minn[ls] == minn[rs] && A[minid[ls]].id < A[minid[rs]].id))
            minn[p] = minn[ls], minid[p] = minid[ls], exitid[p] = exitid[ls];
        else minn[p] = minn[rs], minid[p] = minid[rs], exitid[p] = exitid[rs];
    }
    inline void pushdown(int p)
    {
        if (!addtag[p]) return;
        minn[ls] += addtag[p], minn[rs] += addtag[p], addtag[ls] += addtag[p], addtag[rs] += addtag[p], addtag[p] = 0;
        exitid[ls] = exittag[p], exitid[rs] = exittag[p], exittag[ls] = exittag[p], exittag[rs] = exittag[p], exittag[p] = 0;
    }
    void modify(int l, int r, int p, int ll, int rr, int k, int exit)
    {
        if (l >= ll && r <= rr)
            return (void)(minn[p] += k, addtag[p] += k, exitid[p] = exit, exittag[p] = exit);
        int mid = (l + r) >> 1;
        pushdown(p);
        if (ll <= mid) modify(l, mid, ls, ll, rr, k, exit);
        if (rr > mid) modify(mid + 1, r, rs, ll, rr, k, exit);
        pushup(p);
    }
    void update(int l, int r, int p, int pos, int k)
    {
        if (l == r) return (void)(minn[p] = k);
        int mid = (l + r) >> 1;
        pushdown(p);
        if (pos <= mid) update(l, mid, ls, pos, k); else update(mid + 1, r, rs, pos, k);
        pushup(p);
    }
    void build(int l, int r, int p, int direction)
    {
        if (l == r)
        {
            minid[p] = l, exitid[p] = A[l].near;
            if (A[l].direction == direction) minn[p] = A[l].neardis; else minn[p] = inf;
            return;
        }
        int mid = (l + r) >> 1;
        build(l, mid, ls, direction), build(mid + 1, r, rs, direction), pushup(p);
    }
    void output(int l, int r, int p)
    {
        if (l == r)
        {
            printf("output:id:%d pos:%d near:%d neardis:%d\n", A[l].id, A[l].pos, exitid[p], minn[p]);
            return;
        }
        int mid = l + r >> 1;
        pushdown(p);
        output(l, mid, ls), output(mid + 1, r, rs);
    }
} S, N;
int lower(int x)
{
    int l = 1, r = n, mid, ans = 0;
    while (l <= r)
    {
        mid = (l + r) >> 1;
        if (A[mid].pos <= x) ans = mid, l = mid + 1; else r = mid - 1;
    }
    return ans;
}
int upper(int x)
{
    int l = 1, r = n, mid, ans = n + 10;
    while (l <= r)
    {
        mid = (l + r) >> 1;
        if (A[mid].pos >= x) ans = mid, r = mid - 1; else l = mid + 1;
    }
    return ans;
}
inline void del(int x)
{
    int a = pre[x], b = nex[x];
    pre[b] = a, nex[a] = b;
}
inline void delnode(int x)
{
    if (--limit[x] == 0)
    {
#ifdef DEBUG
        printf("expired:id:%d pos:%d\n", x, pos[x]);
#endif
        if (pos[pre[x]] < pos[x])
        {
            int l = upper(pos[pre[x]] + 1), r = lower(pos[x]);
            if (l <= r)
            {
                if (pos[nex[x]] > pos[x]) N.modify(1, n, 1, l, r, pos[nex[x]] - pos[x], nex[x]);
                else N.modify(1, n, 1, l, r, pos[nex[x]] + L - pos[x], nex[x]);
            }
        }
        else
        {
            int l = lower(pos[x]), r = upper(pos[pre[x]] + 1);
            if (pos[nex[x]] > pos[x])
            {
                if (l > 0 && l <= n) N.modify(1, n, 1, 1, l, pos[nex[x]] - pos[x], nex[x]);
                if (r > 0 && r <= n) N.modify(1, n, 1, r, n, pos[nex[x]] - pos[x], nex[x]);
            }
            else
            {
                if (l > 0 && l <= n) N.modify(1, n, 1, 1, l, pos[nex[x]] + L - pos[x], nex[x]);
                if (r > 0 && r <= n) N.modify(1, n, 1, r, n, pos[nex[x]] + L - pos[x], nex[x]);
            }
        }
        if (pos[nex[x]] > pos[x])
        {
            int l = upper(pos[x]), r = lower(pos[nex[x]] - 1);
            if (l <= r)
            {
                if (pos[pre[x]] < pos[x]) S.modify(1, n, 1, l, r, pos[x] - pos[pre[x]], pre[x]);
                else S.modify(1, n, 1, l, r, pos[x] + L - pos[pre[x]], pre[x]);
            }
        }
        else
        {
            int l = lower(pos[nex[x]] - 1), r = upper(pos[x]);
            if (pos[pre[x]] < pos[x])
            {
                if (l > 0 && l <= n) S.modify(1, n, 1, 1, l, pos[x] - pos[pre[x]], pre[x]);
                if (r > 0 && r <= n) S.modify(1, n, 1, r, n, pos[x] - pos[pre[x]], pre[x]);
            }
            else
            {
                if (l > 0 && l <= n) S.modify(1, n, 1, 1, l, pos[x] + L - pos[pre[x]], pre[x]);
                if (r > 0 && r <= n) S.modify(1, n, 1, r, n, pos[x] + L - pos[pre[x]], pre[x]);
            }
        }
        del(x);
    }
}
#ifdef DEBUG
int ans[maxn];
#endif
inline void alloutput()
{
#ifdef DEBUG
    puts("N:");
    N.output(1, n, 1);
    puts("S:");
    S.output(1, n, 1);
    puts("");
#endif
}
int main()
{
    //freopen("walk.in","r",stdin),freopen("my.out","w",stdout);
    read(n), read(m), read(L);
    for (int i = 1; i <= m; ++i) pre[i] = i - 1, nex[i] = i + 1;
    for (int i = 2; i <= m; ++i) read(pos[i]);
    pre[1] = m, nex[m] = 1, pos[m + 1] = L;
    for (int i = 1; i <= m; ++i) read(limit[i]);
    for (int i = 1; i <= n; ++i) A[i].id = i, read(A[i].direction), read(A[i].pos), A[i].pos %= L;
    std::sort(A + 1, A + 1 + n, cmp);
    int p = 1;
    for (int i = 1; i <= n; ++i)
        if (A[i].direction == 0)
        {
            while (p <= m && A[i].pos > pos[p]) ++p;
            A[i].neardis = pos[p] - A[i].pos, A[i].near = p > m ? p - m : p;
        }
    p = m;
    for (int i = n; i; --i)
        if (A[i].direction == 1)
        {
            while (p > 0 && A[i].pos < pos[p]) --p;
            A[i].neardis = A[i].pos - pos[p], A[i].near = p > m ? 1 : p;
        }
#ifdef DEBUG
    for (int i = 1; i <= n; ++i) printf("id: %d pos: %d near: %d neardis: %d\n", A[i].id, A[i].pos, A[i].near, A[i].neardis);
#endif
    N.build(1, n, 1, 0), S.build(1, n, 1, 1);
#ifdef DEBUG
    alloutput();
#endif
#ifndef DEBUG
    long long ans = 0;
#endif
    for (int t = 1; t <= n; ++t)
    {
        if (N.minn[1] < S.minn[1] || (N.minn[1] == S.minn[1] && A[N.minid[1]].id < A[S.minid[1]].id))
        {
            int exitid = N.exitid[1];
#ifdef DEBUG
            printf("leave: id:%d exitid:%d dis:%d\n", A[N.minid[1]].id, exitid, N.minn[1]);
#endif
            if (limit[exitid] <= 0) continue;
#ifndef DEBUG
            ans ^= 1ll * A[N.minid[1]].id * exitid;
#endif
#ifdef DEBUG
            ans[A[N.minid[1]].id] = exitid;
#endif
            N.update(1, n, 1, N.minid[1], inf);
            delnode(exitid);
        }
        else
        {
            int exitid = S.exitid[1];
#ifdef DEBUG
            printf("leave: id:%d exitid:%d dis:%d\n", A[S.minid[1]].id, exitid, S.minn[1]);
#endif
            if (limit[exitid] <= 0) continue;
#ifndef DEBUG
            ans ^= 1ll * A[S.minid[1]].id * exitid;
#endif
#ifdef DEBUG
            ans[A[S.minid[1]].id] = exitid;
#endif
            S.update(1, n, 1, S.minid[1], inf);
            delnode(exitid);
        }
        alloutput();
    }
#ifndef DEBUG
    printf("%lld\n", ans);
#endif
#ifdef DEBUG
    for (int i = 1; i <= n; ++i) printf("%d %d\n", i, ans[i]);
#endif
    return 0;
}