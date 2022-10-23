#include <cstdio>
#include <algorithm>
#include <vector>
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
const int maxn = 21000;
const long long inf = 1ll << 60;
int n, k, dis[maxn], cost[maxn], range[maxn], L[maxn], R[maxn], w[maxn];
long long sum[maxn], minn[maxn << 2], tag[maxn << 2];
#define ls p << 1
#define rs p << 1 | 1
inline void pushdown(int p)
{
    if (!tag[p]) return;
    minn[ls] += tag[p], minn[rs] += tag[p], tag[ls] += tag[p], tag[rs] += tag[p], tag[p] = 0;
}
inline void pushup(int p) { minn[p] = min(minn[ls], minn[rs]); }
void modify(int l,int r,int p,int pos,long long k)
{
    if (l == r) return (void)(minn[p] = k);
    int mid = (l + r) >> 1;
    pushdown(p);
    if (pos <= mid) modify(l, mid, ls, pos, k); else modify(mid + 1, r, rs, pos, k);
    pushup(p);
}
void modify(int l, int r, int p, int ll, int rr, long long k)
{
    if (l >= ll && r <= rr) return (void)(minn[p] += k, tag[p] += k);
    int mid = (l + r) >> 1;
    pushdown(p);
    if (ll <= mid) modify(l, mid, ls, ll, rr, k);
    if (rr > mid) modify(mid + 1, r, rs, ll, rr, k);
    pushup(p);
}
void build(int l, int r, int p)
{
    tag[p] = 0, minn[p] = 1 << 30;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(l, mid, ls), build(mid + 1, r, rs);
}
vector<int> V[maxn];
long long f[2][maxn];
int main()
{
    read(n), read(k);
    for (int i = 2; i <= n; ++i) read(dis[i]);
    for (int i = 1; i <= n; ++i) read(cost[i]);
    for (int i = 1; i <= n; ++i) read(range[i]);
    for (int i = 1; i <= n; ++i) read(w[i]), sum[i] = sum[i - 1] + w[i];
    for (int i = 1; i <= n; ++i)
    {
        int l = 1, r = i, mid, ans = i;
        while (l <= r)
        {
            mid = (l + r) >> 1;
            if (dis[mid] >= dis[i] - range[i]) ans = mid, r = mid - 1; else l = mid + 1;
        }
        L[i] = ans;
        l = i, r = n, ans = i;
        while (l <= r)
        {
            mid = (l + r) >> 1;
            if (dis[mid] <= dis[i] + range[i]) ans = mid, l = mid + 1; else r = mid - 1;
        }
        R[i] = ans;
    }
    ++n, L[n] = R[n] = n, cost[n] = 0, w[n] = 1 << 30;
    for (int i = 1; i <= n; ++i) V[R[i]].push_back(i);
    long long res = inf;
    int now = 1, last = 0;
    {
        long long tmp = 0;
        for (int i = 1; i <= n; ++i)
        {
            f[last][i] = tmp + cost[i];
            for (vector<int>::iterator it = V[i].begin(); it != V[i].end(); ++it) tmp += w[*it];
        }
        res = f[last][n];
    }
   for (int t = 2; t <= k + 1; ++t)
    {
        build(1, n, 1);
        for (int i = 1; i <= n; ++i)
        {
            f[now][i] = minn[1] + cost[i];
            for (vector<int>::iterator it = V[i].begin(); it != V[i].end(); ++it)
                if (L[*it] > 1) modify(1, n, 1, 1, L[*it] - 1, w[*it]);
            modify(1, n, 1, i, f[last][i]);
        }
        res = min(res, f[now][n]);
        now ^= 1, last ^= 1;
    }
    printf("%lld\n", res);
    return 0;
}