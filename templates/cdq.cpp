#include <algorithm>
#include <cstdio>
const int maxn = 1e5 + 100;
namespace cdq
{
int n;
struct node
{
    int a, b, c, id, cnt;
    int atag, btag;
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
void cdq2(int l, int r)
{
    if(l == r) return;
    int mid = (l + r) >> 1;
    cdq2(l, mid), cdq2(mid + 1, r);
    // sort according to c
    for (int i = l; i <= mid; ++i) B[i].btag = 0;
    for (int i = mid + 1; i <= r; ++i) B[i].btag = 1;
    int p = l, q = mid + 1, k = l;
    while (p <= mid && q <= r)
    {
        if (B[p].c <= B[q].c)
            C[k++] = B[p++];
        else
            C[k++] = B[q++];
    }
    while (p <= mid) C[k++] = B[p++];
    while (q <= r) C[k++] = B[q++];
    for (int i = l; i <= r; ++i) B[i] = C[i];
    // now count the answer
    int num = 0;
    for (int i = l; i <= r; ++i)
    {
        if (B[i].atag && B[i].btag)
            res[B[i].id] += num;
        else if (!B[i].atag && !B[i].btag)
            num += B[i].cnt;
    }
}
void cdq(int l, int r)
{
    if (l == r) return;
    int mid = (l + r) >> 1;
    cdq(l, mid), cdq(mid + 1, r);
    // now [l,mid] [mid+1,r] has been sorted according to b
    for (int i = l; i <= mid; ++i) A[i].atag = 0;
    for (int i = mid + 1; i <= r; ++i) A[i].atag = 1;
    // merge sort to get [l,r] sorted by b
    int p = l, q = mid + 1, k = l;
    while (p <= mid && q <= r)
    {
        if (A[p].b <= A[q].b)
            B[k++] = A[p++];
        else
            B[k++] = A[q++];
    }
    while (p <= mid) B[k++] = A[p++];
    while (q <= r) B[k++] = A[q++];
    // A should be sorted by b
    for(int i = l;i<=r;++i) A[i] = B[i];
    // now [l,r] sorted by b, cdq2 to get the answer 
    cdq2(l, r);
}
}  // namespace cdq
int ans[maxn];
int main()
{
    int _n, k;
    using namespace cdq;
    scanf("%d%d", &cdq::n, &k);
    _n = n;
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