#include <cstdio>
const int maxn = 1e6;
#define ls (p << 1)
#define rs (p << 1 | 1)
int n, m, A[maxn];
long long tag[maxn], sum[maxn];
inline void pushup(int p)
{
    sum[p] = sum[ls] + sum[rs];
}
inline void pushdown(int l, int r, int p)
{
    if (!tag[p]) return;
    int mid = (l + r) >> 1;
    sum[ls] += tag[p] * (mid - l + 1);
    sum[rs] += tag[p] * (r - mid);
    tag[ls] += tag[p], tag[rs] += tag[p];
    tag[p] = 0;
}
void add(int l, int r, int p, int ll, int rr, long long k)
{
    if (l >= ll && r <= rr)
    {
        sum[p] += k * (r - l + 1), tag[p] += k;
        return;
    }
    int mid = (l + r) >> 1;
    pushdown(l, r, p);
    if (ll <= mid) add(l, mid, ls, ll, rr, k);
    if (rr > mid) add(mid + 1, r, rs, ll, rr, k);
    pushup(p);
}
long long ask(int l, int r, int p, int ll, int rr)
{
    if (l >= ll && r <= rr) return sum[p];
    int mid = (l + r) >> 1;
    long long res = 0;
    pushdown(l,r,p);
    if (ll <= mid) res = ask(l, mid, ls, ll, rr);
    if (rr > mid) res += ask(mid + 1, r, rs, ll, rr);
    return res;
}
void build(int l, int r, int p)
{
    if (l == r) return (void)(sum[p] = A[l]);
    int mid = (l + r) >> 1;
    build(l, mid, ls), build(mid + 1, r, rs), pushup(p);
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%d", A + i);
    build(1,n,1);
    while (m--)
    {
        int opt, l, r, k;
        scanf("%d%d%d", &opt, &l, &r);
        if (opt == 1)
            scanf("%d", &k), add(1, n, 1, l, r, k);
        else
            printf("%lld\n", ask(1, n, 1, l, r));
    }
    return 0;
}