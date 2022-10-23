#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
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
    static int flag;
    flag = 1, r = 0;
    for (c = nc(); !isdigit(c); c = nc()) if (c == '-') flag = -1;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r *= flag;
}
const int maxn = 2e5 + 100;
const int maxm = 1e6;
int n, m, p;
int costa[maxm + 100], costb[maxm + 100];
vector<pair<int,int> > V[maxm + 100];
int maxx[maxm << 2], tag[maxm << 2];
#define ls p << 1
#define rs p << 1 | 1
inline void pushup(int p) { maxx[p] = max(maxx[ls], maxx[rs]); }
inline void pushdown(int p) { if (tag[p]) maxx[ls] += tag[p], maxx[rs] += tag[p], tag[ls] += tag[p], tag[rs] += tag[p], tag[p] = 0; }
void build(int l, int r, int p)
{
    if (l == r) return (void)(maxx[p] = -costb[l]);
    int mid = l + r >> 1;
    build(l, mid, ls), build(mid + 1, r, rs), pushup(p);
}
void modify(int l,int r,int p,int ll,int rr,int k)
{
    if (l >= ll && r <= rr) return (void)(maxx[p] += k, tag[p] += k);
    pushdown(p);
    int mid = (l + r) >> 1;
    if (ll <= mid) modify(l, mid, ls, ll, rr, k);
    if (rr > mid) modify(mid + 1, r, rs, ll, rr, k);
    pushup(p);
}
int main()
{
    read(n), read(m), read(p);
    memset(costa, 0x3f, sizeof(costa)), memset(costb, 0x3f, sizeof(costb));
    int maxa = 0, maxb = 0;
    for (int i = 1, a, cost; i <= n; ++i) read(a), read(cost), costa[a] = min(costa[a], cost), maxa = max(maxa, a);
    for (int i = 1, b, cost; i <= m; ++i) read(b), read(cost), costb[b] = min(costb[b], cost), maxb = max(maxb, b);
    for (int i = maxa - 1; i; --i) costa[i] = min(costa[i], costa[i + 1]);
    for (int i = maxb - 1; i; --i) costb[i] = min(costb[i], costb[i + 1]);
    for (int i = 1, x, y, z; i <= p; ++i)
        read(x), read(y), read(z), V[x].push_back(make_pair(y, z));
    build(1, maxb, 1);
    int res = -2100000000;
    for (int i = 1; i <= maxa; ++i)
    {
        res = max(res, maxx[1] - costa[i]);
        for (vector<pair<int, int> >::iterator it = V[i].begin(); it != V[i].end(); ++it)
            if (it->first < maxb) modify(1, maxb, 1, it->first + 1, maxb, it->second);
    }
    printf("%d\n", res);
    return 0;
}