#include <algorithm>
#include <cstdio>
const int maxn = 2e5 + 100;

namespace PersistentDSU
{
struct node
{
    int ls, rs;
    int val, rnk;
} A[maxn << 5];
int a[maxn], cnt;
inline void clear() { cnt = 0; }
inline int newnode() { return ++cnt; }
inline int newnode(int old)
{
    if (!old) return newnode();
    A[++cnt] = A[old];
    return cnt;
}
int build(int l, int r)
{
    int p = newnode();
    if (l == r) return A[p].val = l, A[p].rnk = 1, p;
    int mid = (l + r) >> 1;
    A[p].ls = build(l, mid), A[p].rs = build(mid + 1, r);
    return p;
}
int modify_val(int l, int r, int p, int pos, int k)
{
    int now = newnode(p);
    if (l == r) return A[now].val = k, now;
    int mid = (l + r) >> 1;
    if (pos <= mid)
        A[now].ls = modify_val(l, mid, A[now].ls, pos, k);
    else
        A[now].rs = modify_val(mid + 1, r, A[now].rs, pos, k);
    return now;
}
int add_rnk(int l, int r, int p, int pos, int k)
{
    int now = newnode(p);
    if (l == r) return ++A[now].rnk, now;
    int mid = (l + r) >> 1;
    if (pos <= mid)
        A[now].ls = add_rnk(l, mid, A[now].ls, pos, k);
    else
        A[now].rs = add_rnk(mid + 1, r, A[now].rs, pos, k);
    return now;
}
node ask(int l, int r, int p, int pos)
{
    if (l == r) return A[p];
    int mid = (l + r) >> 1;
    if (pos <= mid)
        return ask(l, mid, A[p].ls, pos);
    else
        return ask(mid + 1, r, A[p].rs, pos);
}

int n, roots[maxn];
void init()
{
    roots[0] = build(1, n);
}
node find(int root, int x)
{
    node fa = ask(1, n, root, x);
    if (fa.val == x) return fa;
    return find(root, fa.val);
}
int merge(int root, int x, int y)
{
    node rx = find(root, x), ry = find(root, y);
    if (rx.rnk > ry.rnk) std::swap(rx, ry);
    root = modify_val(1, n, root, rx.val, ry.val);
    root = add_rnk(1, n, root, ry.val, 1);
    return root;
}
bool same(int root, int x, int y)
{
    return find(root, x).val == find(root, y).val;
}
}  // namespace PersistentDSU

int n, m;
int main()
{
    scanf("%d%d", &n, &m);
    PersistentDSU::n = n;
    PersistentDSU::init();
    namespace d = PersistentDSU;
    for (int t = 1; t <= m; ++t)
    {
        int opt, a, b;
        scanf("%d", &opt);
        if (opt == 1)
            scanf("%d%d", &a, &b), d::roots[t] = d::merge(d::roots[t - 1], a, b);
        else if (opt == 2)
            scanf("%d", &a), d::roots[t] = d::roots[a];
        else
            d::roots[t] = d::roots[t - 1], scanf("%d%d", &a, &b), puts(d::same(d::roots[t], a, b) ? "1" : "0");
    }
    return 0;
}