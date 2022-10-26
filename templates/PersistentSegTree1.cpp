#include <algorithm>
#include <cstdio>

const int maxn = 1e6 + 10;

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
        if (now.ls) now.sum += A[now.ls].sum;
        if (now.rs) now.sum += A[now.rs].sum;
    }
    int build(int l, int r)
    {
        int p = newnode();
        if (l == r) return A[p].sum = a[l], p;
        int mid = (l + r) >> 1;
        A[p].ls = build(l, mid), A[p].rs = build(mid + 1, r);
        pushup(p);
        return p;
    }
    int modify(int l, int r, int p, int pos, int k)
    {
        int now = newnode(p);
        if (l == r) return A[now].sum = k, now;
        int mid = (l + r) >> 1;
        if (pos <= mid)
            A[now].ls = modify(l, mid, A[now].ls, pos, k);
        else
            A[now].rs = modify(mid + 1, r, A[now].rs, pos, k);
        pushup(now);
        return now;
    }
    int add(int l,int r,int p, int pos, int k)
    {
        int now = newnode(p);
        if(l == r)
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
int n, m, root[maxn];
int main()
{
    scanf("%d%d", &n,&m);
    for (int i = 1; i <= n; ++i) scanf("%d", T.a + i);
    root[0] = T.build(1, n);
    for (int t = 1; t <= m; ++t)
    {
        int v, opt, pos, k;
        scanf("%d%d%d", &v, &opt, &pos);
        if (opt == 1)
        {
            scanf("%d", &k);
            root[t] = T.modify(1, n, root[v], pos, k);
        }
        else
            root[t] = root[v], printf("%d\n", T.ask(1, n, root[t], pos, pos));
    }
    return 0;
}