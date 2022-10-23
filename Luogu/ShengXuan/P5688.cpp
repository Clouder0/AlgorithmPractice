#include <algorithm>
#include <cctype>
#include <cstdio>
using namespace std;
const int bufSize = 1e6;
#define DEBUG
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
    r = 0;
    for (c = nc(); !isdigit(c); c = nc());
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r;
}
const int maxn = 2e5 + 100;
int n, m, L, limit[maxn], pre[maxn], nex[maxn], exitpos[maxn];
struct person
{
    int pos, direction, near, neardis;
} P[maxn];
int pid[maxn];
inline bool cmp(const int& a, const int& b) { return P[a].pos < P[b].pos; }
const int inf = 1 << 30;
struct segtree
{
#define ls p << 1
#define rs p << 1 | 1
    int minn[maxn << 2], minid[maxn << 2], exitid[maxn << 2], tag[maxn << 2], exittag[maxn << 2];
    inline void pushup(int p)
    {
        minn[p] = std::min(minn[ls], minn[rs]);
        if (minn[ls] == minn[p]) exitid[p] = exitid[ls], minid[p] = minid[ls];
        else exitid[p] = exitid[rs], minid[p] = minid[rs];
    }
    inline void pushdown(int p)
    {
        if (tag[p]) minn[ls] += tag[p], minn[rs] += tag[p], tag[ls] += tag[p], tag[rs] += tag[p], tag[p] = 0;
        if (exittag[p]) exitid[ls] = exitid[rs] = exittag[ls] = exittag[rs] = exittag[p];
    }
    void modify(int l, int r, int p, int ll, int rr, int k, int exit)
    {
        if (l >= ll && r <= rr) return (void)(minn[p] += k, tag[p] += k, exitid[p] = exit, exittag[p] = exit);
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
            minid[p] = l, exitid[p] = P[pid[l]].near;
            if (direction == P[pid[l]].direction) minn[p] = P[pid[l]].neardis; else minn[p] = inf;
            return;
        }
        int mid = (l + r) >> 1;
        build(l, mid, ls, direction), build(mid + 1, r, rs, direction), pushup(p);
    }
} S, N;
inline void del(int x)
{
    int a = pre[x], b = nex[x];
    nex[a] = b, pre[b] = a;
}
inline int upper(int pos)
{
    int l = 1, r = n, mid, ans = -1;
    while (l <= r)
    {
        mid = (l + r) >> 1;
        if (P[pid[mid]].pos >= pos) ans = mid, r = mid - 1;
        else l = mid + 1;
    }
    return ans;
}
inline int lower(int pos)
{
    int l = 1, r = n, mid, ans = -1;
    while (l <= r)
    {
        mid = (l + r) >> 1;
        if (P[pid[mid]].pos <= pos) ans = mid, l = mid + 1;
        else r = mid - 1;
    }
    return ans;
}
void dellimit(int x)
{
    if (--limit[x] == 0)
    {
        int l = upper(exitpos[pre[x]] + 1), r = lower(exitpos[x]);
        if (l <= r) N.modify(1, n, 1, l, r, exitpos[nex[x]] - exitpos[x], nex[x]);
        l = upper(exitpos[x]), r = lower(exitpos[nex[x]] - 1);
        if (l <= r) S.modify(1, n, 1, l, r, exitpos[x] - exitpos[pre[x]], pre[x]);
        del(x);
    }
}
int main()
{
    read(n), read(m), read(L);
    exitpos[1] = 0, pre[1] = 0, nex[1] = 2, exitpos[m + 1] = L;
    for (int i = 2; i <= m; ++i) read(exitpos[i]), pre[i] = i - 1, nex[i] = i + 1;
    for (int i = 1; i <= m; ++i) read(limit[i]);
    for (int i = 1; i <= n; ++i) read(P[i].direction), read(P[i].pos), pid[i] = i, P[i].neardis = 1 << 30;
    sort(pid + 1, pid + 1 + n, cmp);
    for (int i = 1; i <= n; ++i)
        if (P[i].pos == 0 || P[i].pos == L) P[i].near = 1, P[i].neardis = 0;
    int l = 1, r = 0;
    for (int i = 1; i <= m; ++i)
    {
        while (l <= n && P[pid[l]].pos <= exitpos[i]) ++l;
        if (i == m) r = n;
        while (r < n && P[pid[r + 1]].pos <= exitpos[i + 1]) ++r;
        for (int j = l; j <= r; ++j)
            if (P[pid[j]].direction == 0) P[pid[j]].near = i + 1, P[pid[j]].neardis = exitpos[i + 1] - P[pid[j]].pos;
        l = r + 1;
    }
    l = 1, r = 0;
    for (int i = 1; i <= m; ++i)
    {
        while (l <= n && P[pid[l]].pos < exitpos[i]) ++l;
        if (i == m) r = n;
        while (r < n && P[pid[r + 1]].pos < exitpos[i + 1]) ++r;
        for (int j = l; j <= r; ++j)
            if (P[pid[j]].direction == 1) P[pid[j]].near = i, P[pid[j]].neardis = P[pid[j]].pos - exitpos[i];
        l = r + 1;
    }
    N.build(1, n, 1, 0), S.build(1, n, 1, 1);
    //for(int i = 1;i<=n;++i) printf("person:%d pos:%d near:%d neardis:%d\n",i,P[i].pos,P[i].near,P[i].neardis);
    long long ans = 0;
    for (int t = 1; t <= n; ++t)
    {
        if (N.minn[1] < S.minn[1] || (N.minn[1] == S.minn[1] && pid[N.minid[1]] < pid[S.minid[1]]))
        {
            int id = N.minid[1], exitid = N.exitid[1];
            if (exitid == m + 1) exitid = 1;
            if (limit[exitid] <= 0) continue;
            ans ^= 1ll * pid[id] * exitid;
            N.update(1, n, 1, id, inf);
            dellimit(exitid);
        }
        else
        {
            int id = S.minid[1], exitid = S.exitid[1];
            if (exitid == m + 1) exitid = 1;
            if (limit[exitid] <= 0) continue;
            ans ^= 1ll * pid[id] * exitid;
            S.update(1, n, 1, id, inf);
            dellimit(exitid);
        }
    }
    printf("%lld\n", ans);
    return 0;
}