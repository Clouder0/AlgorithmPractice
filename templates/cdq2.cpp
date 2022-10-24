#include <algorithm>
#include <cstdio>
const int maxn = 2e5 + 100;
namespace BitTree
{
int n;
int sum[maxn], tag[maxn], now;
inline void clear() { ++now; }
inline void check(int x)
{
    if (tag[x] != now) sum[x] = 0, tag[x] = now;
}
void add(int x, int k)
{
    for (; x <= n; x += (x & -x)) check(x), sum[x] += k;
}
int ask(int x)
{
    int res = 0;
    for (; x > 0; x -= (x & -x)) check(x), res += sum[x];
    return res;
}
}  // namespace BitTree
namespace cdq
{
int n;
struct node
{
    int a, b, c, id, cnt;
} A[maxn], B[maxn], C[maxn];
int res[maxn];
bool cmpa(const node& x, const node& y)
{
    if (x.a != y.a) return x.a < y.a;
    if (x.b != y.b) return x.b < y.b;
    return x.c < y.c;
}
void init()
{
    for (int i = 1; i <= n; ++i) A[i].id = i, A[i].cnt = 1;
    for (int i = 1; i <= n; ++i) res[i] = 0;
    std::sort(A + 1, A + 1 + n, cmpa);
    int tot = 0;
    for (int i = 2; i <= n; ++i)
        if (A[i].a == A[i - 1].a && A[i].b == A[i - 1].b && A[i].c == A[i - 1].c)
            A[i].cnt = A[i - 1].cnt + 1;
        else
            B[++tot] = A[i - 1];
    B[++tot] = A[n];
    n = tot;
    for (int i = 1; i <= n; ++i) A[i] = B[i];
}
void cdq(int l, int r)
{
    if (l == r) return;
    int mid = (l + r) >> 1;
    cdq(l, mid), cdq(mid + 1, r);
    // now [l,mid] [mid+1,r] has been sorted according to b
    // merge sort to get [l,r] sorted by b
    int p = l, q = mid + 1, k = l;
    while (p <= mid && q <= r)
    {
        if (A[p].b <= A[q].b)
        {
            BitTree::add(A[p].c, A[p].cnt);
            B[k++] = A[p++];
        }
        else
        {
            res[A[q].id] += BitTree::ask(A[q].c);
            B[k++] = A[q++];
        }
    }
    while (p <= mid) B[k++] = A[p++];
    while (q <= r) res[A[q].id] += BitTree::ask(A[q].c), B[k++] = A[q++];
    BitTree::clear();
    // A should be sorted by b
    for (int i = l; i <= r; ++i) A[i] = B[i];
}
}  // namespace cdq
int ans[maxn];
int main()
{
    int _n, k;
    using namespace cdq;
    scanf("%d%d", &cdq::n, &k);
    _n = n;
    BitTree::n = k;
    for (int i = 1; i <= cdq::n; ++i)
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        A[i].a = a, A[i].b = b, A[i].c = c;
    }
    cdq::init();
    cdq::cdq(1, cdq::n);
    //    for(int i = 1;i<=cdq::n;++i)
    //        printf("[%d]%d %d %d %d:%d\n",A[i].id,A[i].a,A[i].b,A[i].c,A[i].cnt, res[A[i].id] + A[i].cnt - 1);
    for (int i = 1; i <= cdq::n; ++i) ans[res[A[i].id] + A[i].cnt] += A[i].cnt;
    for (int i = 1; i <= _n; ++i) printf("%d\n", ans[i]);
    return 0;
}