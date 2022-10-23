#include <algorithm>
#include <cstdio>
using namespace std;
const int maxn = 2e5 + 100;
int n, m;
int root[maxn], rnk[maxn << 5], fa[maxn << 5], L[maxn << 5], R[maxn << 5], ind;
int modifyfa(int l, int r, int p, int pos, int k)
{
    int now = ++ind;
    L[now] = L[p], R[now] = R[p], fa[now] = fa[p], rnk[now] = rnk[p];
    if (l == r) return fa[now] = k, now;
    int mid = l + r >> 1;
    if (pos <= mid) L[now] = modifyfa(l, mid, L[now], pos, k);
    else R[now] = modifyfa(mid + 1, r, R[now], pos, k);
    return now;
}
int modifyrnk(int l, int r, int p, int pos, int k)
{
    int now = ++ind;
    L[now] = L[p], R[now] = R[p], fa[now] = fa[p], rnk[now] = rnk[p];
    if (l == r) return rnk[now] = k, now;
    int mid = l + r >> 1;
    if (pos <= mid) L[now] = modifyrnk(l, mid, L[now], pos, k);
    else R[now] = modifyrnk(mid + 1, r, R[now], pos, k);
    return now;
}
int askfa(int l, int r, int p, int pos)
{
    if (l == r) return fa[p];
    int mid = l + r >> 1;
    if (pos <= mid)return askfa(l, mid, L[p], pos);
    else return askfa(mid + 1, r, R[p], pos);
}
int askrnk(int l, int r, int p, int pos)
{
    if (l == r) return rnk[p];
    int mid = l + r >> 1;
    if (pos <= mid) return askrnk(l, mid, L[p], pos);
    else return askrnk(mid + 1, r, R[p], pos);
}
int find(int x, int rt)
{
    int f = askfa(1, n, rt, x);
    return f == x ? x : find(f, rt);
}
void merge(int x, int y, int& rt)
{
    x = find(x, rt), y = find(y, rt);
    if (x == y) return;
    int rnkx = askrnk(1, n, rt, x), rnky = askrnk(1, n, rt, y);
    if (rnkx == rnky) rt = modifyfa(1, n, rt, y, x), rt = modifyrnk(1, n, rt, x, rnkx + 1);
    else if (rnkx < rnky) rt = modifyfa(1, n, rt, x, y);
    else rt = modifyfa(1, n, rt, y, x);
}
void build(int l, int r, int& p)
{
    p = ++ind;
    if (l == r) return (void)(fa[p] = l);
    int mid = l + r >> 1;
    build(l, mid, L[p]), build(mid + 1, r, R[p]);
}
int main()
{
    scanf("%d %d", &n, &m);
    build(1, n, root[0]);
    for (int i = 1; i <= m; ++i)
    {
        int opt, a, b, k;
        scanf("%d", &opt);
        if (opt == 2) scanf("%d", &k); else scanf("%d %d", &a, &b);
        root[i] = root[i - 1];
        if (opt == 1) merge(a, b, root[i]);
        else if (opt == 2) root[i] = root[k];
        else
        {
            int f1 = find(a, root[i]), f2 = find(b, root[i]);
            if (f1 == f2) puts("1");
            else puts("0");
        }
    }
    return 0;
}