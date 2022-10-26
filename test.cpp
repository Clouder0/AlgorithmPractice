#include <algorithm>
#include <cstdio>

const int maxn = 2e5 + 10;

struct PersistentSegTree
{
    struct node
    {
        int ls, rs;
        long long sum, tag;
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
    int seg_add(int l, int r, int p, int ll, int rr, int k)
    {
        int now = newnode(p);
        A[now].sum += 1ll * k * (std::min(rr,r) - std::max(l,ll) + 1);
        if (l >= ll && r <= rr) return A[now].tag += k, now;
        int mid = (l + r) >> 1;
        if (ll <= mid) A[now].ls = seg_add(l, mid, A[now].ls, ll, rr, k);
        if (rr > mid) A[now].rs = seg_add(mid + 1,r,A[now].rs, ll, rr, k);
        return now;
    }
    long long ask(int l,int r,int p, int ll, int rr, long long tagsum)
    {
        if(!p) return 0;
        if (l >= ll && r <= rr) return A[p].sum + tagsum * (r - l + 1);
        int mid = (l + r) >> 1;
        long long ret = 0;
        tagsum += A[p].tag;
        if (ll <= mid) ret += ask(l,mid,A[p].ls, ll, rr, tagsum);
        if (rr > mid) ret += ask(mid + 1,r,A[p].rs, ll, rr, tagsum);
        return ret;
    }
};
PersistentSegTree T;
int n, m, root[maxn];
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%d", T.a + i);
    for (int i = 1; i <= n; ++i) root[0] = T.seg_add(1,n,root[0], i, i, T.a[i]);
    for (int t = 1; t <= m; ++t)
    {
        int opt, x, y, k;
        scanf("%d%d%d", &opt, &x, &y);
        if (opt == 1)
            scanf("%d", &k), root[t] = T.seg_add(1,n,root[t - 1], x, y, k);
        else
            root[t] = root[t - 1], printf("%lld\n", T.ask(1,n,root[t], x, y, 0));
    }
    return 0;
}
