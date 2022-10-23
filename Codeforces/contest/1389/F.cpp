#include <algorithm>
#include <cstdio>
#include <ctype.h>
#include <vector>
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
const int maxn = 4e5 + 100;
int n;
struct seg
{
    int l, r, t;
} S[maxn];
int H[maxn], cnt;
vector<pair<int, int> > V[maxn];
struct SegmentTree
{
    int maxx[maxn << 2], tag[maxn << 2];
    void pushdown(int p)
    {
        if (!tag[p]) return;
        maxx[p << 1] += tag[p], maxx[p << 1 | 1] += tag[p];
        tag[p << 1] += tag[p], tag[p << 1 | 1] += tag[p];
        tag[p] = 0;
    }
    void add(int l, int r, int p, int ll, int rr, int k)
    {
        if (ll > rr) return;
        if (l >= ll && r <= rr)
        {
            maxx[p] += k;
            tag[p] += k;
            return;
        }
        pushdown(p);
        int mid = l + r >> 1;
        if (ll <= mid) add(l, mid, p << 1, ll, rr, k);
        if (rr > mid) add(mid + 1, r, p << 1 | 1, ll, rr, k);
        maxx[p] = max(maxx[p << 1], maxx[p << 1 | 1]);
    }
    void modify(int l, int r, int p, int pos, int k)
    {
        if (l == r) return (void)(tag[p] = 0, maxx[p] = k);
        pushdown(p);
        int mid = l + r >> 1;
        if (pos <= mid) modify(l, mid, p << 1, pos, k);
        else modify(mid + 1, r, p << 1 | 1, pos, k);
        maxx[p] = max(maxx[p << 1], maxx[p << 1 | 1]);
    }
} T[2];
int main()
{
    read(n);
    H[++cnt] = 0;
    for (int i = 1; i <= n; ++i) read(S[i].l), read(S[i].r), read(S[i].t), H[++cnt] = S[i].l, H[++cnt] = S[i].r;
    sort(H + 1, H + 1 + cnt), cnt = unique(H + 1, H + 1 + cnt) - H - 1;
    for (int i = 1; i <= n; ++i)
    {
        S[i].l = lower_bound(H + 1, H + 1 + cnt, S[i].l) - H;
        S[i].r = lower_bound(H + 1, H + 1 + cnt, S[i].r) - H;
        V[S[i].r].push_back(make_pair(S[i].l, S[i].t - 1));
    }
    for (int i = 1; i <= cnt; ++i)
    {
        for (vector<pair<int, int> >::iterator it = V[i].begin(); it != V[i].end(); ++it)
        {
            int L = it->first, k = it->second;
            T[k].add(1, cnt, 1, 1, L - 1, 1);
        }
        int maxnum = max(T[0].maxx[1], T[1].maxx[1]);
        T[0].modify(1, cnt, 1, i, maxnum);
        T[1].modify(1, cnt, 1, i, maxnum);
    }
    printf("%d\n", max(T[0].maxx[1], T[1].maxx[1]));
    return 0;
}