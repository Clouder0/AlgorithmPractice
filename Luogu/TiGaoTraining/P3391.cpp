#include <cstdio>
#include <algorithm>
#include <cstdlib>
const int maxn = 1e5 + 100;
const int magic = (1 << 15) - 1;
inline int rnd() { return (rand() << 15) ^ (rand() & magic); }
int n, m, val[maxn],pri[maxn], L[maxn], R[maxn], sz[maxn], tag[maxn], tot, root;
inline int newnode(int x = 0) { return pri[++tot] = rnd(), val[tot] = x, L[tot] = R[tot] = 0, sz[tot] = 1, tot; }
inline void pushup(int p) { sz[p] = sz[L[p]] + sz[R[p]] + 1; }
inline void pushdown(int p)
{
    if (!tag[p]) return;
    std::swap(L[p], R[p]), tag[L[p]] ^= 1, tag[R[p]] ^= 1, tag[p] = 0;
}
void split(int now, int k, int& x, int& y)
{
    if(!now) return (void)(x = y = 0);
    pushdown(now);
    if (k <= sz[L[now]]) y = now, split(L[now], k, x, L[now]);
    else x = now, split(R[now], k - sz[L[now]] - 1, R[now], y);
    pushup(now);
}
int merge(int x, int y)
{
    if (!x || !y) return x + y;
    pushdown(x), pushdown(y);
    if (pri[x] > pri[y]) return R[x] = merge(R[x], y), pushup(x), x;
    return L[y] = merge(x, L[y]), pushup(y), y;
}
void reverse(int l, int r)
{
    int s, m, b;
    split(root, l - 1, s, m), split(m, r - l + 1, m, b);
    tag[m] ^= 1, root = merge(merge(s, m), b);
}
int build(int l, int r)
{
    if(l > r) return 0;
    if (l == r) return newnode(l);
    int mid = (l + r) >> 1, u = newnode(mid);
    L[u] = build(l, mid - 1), R[u] = build(mid + 1, r);
    pushup(u);
    return u;
}
void output(int p)
{
    if (!p) return;
    pushdown(p);
    output(L[p]), printf("%d ", val[p]), output(R[p]);
}
int main()
{
    scanf("%d %d", &n, &m);
    root = build(1, n);
    for (int i = 1, l, r; i <= m; ++i) 
        scanf("%d %d", &l, &r), reverse(l, r);
    output(root);
    return 0;
}