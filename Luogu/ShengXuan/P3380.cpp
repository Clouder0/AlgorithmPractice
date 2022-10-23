#include <cstdio>
#include <algorithm>
#include <set>
#include <cstdlib>
#include <cctype>
#include <ctime>
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
const int maxn = 5e6 + 100;
int n, m, a[maxn], root[maxn << 2], L[maxn], R[maxn], sz[maxn], val[maxn], pri[maxn], ind;
namespace Treap
{
inline int newnode(int v = 0) { return ++ind, L[ind] = R[ind] = 0, sz[ind] = 1, val[ind] = v, pri[ind] = rand(), ind; }
inline void pushup(int p) { sz[p] = sz[L[p]] + sz[R[p]] + 1; }
int merge(int x, int y)
{
    if (!x || !y) return x + y;
    if (pri[x] < pri[y]) return R[x] = merge(R[x], y), pushup(x), x;
    else return L[y] = merge(x, L[y]), pushup(y), y;
}
void split(int p, int k, int& x, int& y)
{
    if (!p) return (void)(x = y = 0);
    if (val[p] <= k) x = p, split(R[x], k, R[x], y);
    else y = p, split(L[y], k, x, L[y]);
    pushup(p);
}
void ins(int& root, int k)
{
    int s, b;
    split(root, k, s, b);
    root = merge(merge(s, newnode(k)), b);
}
void del(int& root,int k)
{
    int s, m, b;
    split(root, k - 1, s, b), split(b, k, m, b);
    m = merge(L[m], R[m]);
    root = merge(s, merge(m, b));
}
int ask(int& root, int k)
{
    //ask how many numbers are <= k
    int s, b, res;
    split(root, k, s, b), res = sz[s], root = merge(s, b);
    return res;
}
int pre(int& root,int k)
{
    int s, b, p, res;
    split(root, k - 1, s, b);
    p = s;
    while (R[p]) p = R[p];
    res = val[p], root = merge(s, b);
    if (!p) res = -2147483647;
    return res;
}
int nex(int& root, int k)
{
    int s, b, p, res;
    split(root, k, s, b);
    p = b;
    while (L[p]) p = L[p];
    res = val[p], root = merge(s, b);
    if (!p) res = 2147483647;
    return res;
}
}  // namespace Treap
#define ls p << 1
#define rs p << 1 | 1
void ins(int l, int r, int p, int pos, int k)
{
    Treap::ins(root[p], k);
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (pos <= mid) ins(l, mid, ls, pos, k);
    else ins(mid + 1, r, rs, pos, k);
}
void del(int l, int r, int p, int pos, int k)
{
    Treap::del(root[p], k);
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (pos <= mid) del(l, mid, ls, pos, k);
    else del(mid + 1, r, rs, pos, k);
}
int ask(int l, int r, int p, int ll, int rr, int k)
{
    //ask how many are <= k
    if (l >= ll && r <= rr) return Treap::ask(root[p], k);
    int mid = (l + r) >> 1, res = 0;
    if (ll <= mid) res += ask(l, mid, ls, ll, rr, k);
    if (rr > mid) res += ask(mid + 1, r, rs, ll, rr, k);
    return res;
}
int askkth(int ll, int rr, int k)
{
    //ask the number value ranking k
    int l = 0, r = 100000000, mid, ans = -1;
    while(l <= r)
    {
        mid = (l + r) >> 1;
        if (ask(1, n, 1, ll, rr, mid - 1) + 1 > k) r = mid - 1; else ans = mid, l = mid + 1;
    }
    return ans;
}
std::set<int> S;
void pre(int l, int r, int p, int ll, int rr, int k)
{
    if (l >= ll && r <= rr) return (void)(S.insert(Treap::pre(root[p], k)));
    int mid = (l + r) >> 1;
    if (ll <= mid) pre(l, mid, ls, ll, rr, k);
    if (rr > mid) pre(mid + 1, r, rs, ll, rr, k);
}
void nex(int l, int r, int p, int ll, int rr, int k)
{
    if (l >= ll && r <= rr) return (void)(S.insert(Treap::nex(root[p], k)));
    int mid = (l + r) >> 1;
    if (ll <= mid) nex(l, mid, ls, ll, rr, k);
    if (rr > mid) nex(mid + 1, r, rs, ll, rr, k);
}
int main()
{
    srand(time(0));
    read(n), read(m);
    for (int i = 1; i <= n; ++i) read(a[i]), ins(1, n, 1, i, a[i]);
    for (int i = 1, opt, l, r, k; i <= m; ++i)
    {
        read(opt);
        if (opt == 1) read(l), read(r), read(k), printf("%d\n", ask(1, n, 1, l, r, k - 1) + 1);
        else if (opt == 2) read(l), read(r), read(k), printf("%d\n", askkth(l, r, k));
        else if (opt == 3) read(l), read(k), del(1, n, 1, l, a[l]), a[l] = k, ins(1, n, 1, l, a[l]);
        else if (opt == 4) read(l), read(r), read(k), S.clear(), pre(1, n, 1, l, r, k), printf("%d\n", *S.rbegin());
        else if (opt == 5) read(l), read(r), read(k), S.clear(), nex(1, n, 1, l, r, k), printf("%d\n", *S.begin());
    }
    return 0;
}