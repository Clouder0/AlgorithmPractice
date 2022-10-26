#include <algorithm>
#include <cstdio>

const int maxn = 1e6 + 10;

namespace KTH
{
struct PersistentSegTree
{
    struct node
    {
        int ls, rs;
        int sum;
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
    void pushup(int p)
    {
        node& now = A[p];
        now.sum = 0;
        if (now.ls) now.sum += A[now.ls].sum;
        if (now.rs) now.sum += A[now.rs].sum;
    }
    int add(int l, int r, int p, int pos, int k)
    {
        int now = newnode(p);
        if (l == r)
        {
            A[now].sum += k;
            return now;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid)
            A[now].ls = add(l, mid, A[now].ls, pos, k);
        else
            A[now].rs = add(mid + 1, r, A[now].rs, pos, k);
        pushup(now);
        return now;
    }
    int ask(int l, int r, int p, int ll, int rr)
    {
        if (!p) return 0;
        if (l >= ll && r <= rr) return A[p].sum;
        int mid = (l + r) >> 1;
        int ret = 0;
        if (ll <= mid) ret += ask(l, mid, A[p].ls, ll, rr);
        if (rr > mid) ret += ask(mid + 1, r, A[p].rs, ll, rr);
        return ret;
    }
};
PersistentSegTree T;
int n, a[maxn], root[maxn], H[maxn], cnt;
void init()
{
    for (int i = 1; i <= n; ++i) H[i] = a[i];
    std::sort(H + 1, H + n + 1), cnt = std::unique(H + 1, H + n + 1) - H - 1;
    for (int i = 1; i <= n; ++i) a[i] = std::lower_bound(H + 1, H + cnt + 1, a[i]) - H;
    root[0] = 0;
    for (int i = 1; i <= n; ++i) root[i] = T.add(1, cnt, root[i - 1], a[i], 1);
}
int kth(int l, int r, int p1, int p2, int k)
{
    if (l == r) return l;
    int mid = (l + r) >> 1;
    if (T.A[T.A[p2].ls].sum - T.A[T.A[p1].ls].sum >= k) return kth(l, mid, T.A[p1].ls, T.A[p2].ls, k);
    return kth(mid + 1, r, T.A[p1].rs, T.A[p2].rs, k - (T.A[T.A[p2].ls].sum - T.A[T.A[p1].ls].sum));
}
int query_kth(int l, int r, int k)
{
    return H[kth(1, cnt, root[l - 1], root[r], k)];
}
}  // namespace KTH
int main()
{

    return 0;
}