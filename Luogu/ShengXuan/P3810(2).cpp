#include <algorithm>
#include <cstdio>

template <typename T>
void read(T& r)
{
    static char c;
    r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar())
        ;
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar())
        ;
}
const int maxn = 2e5 + 100;
struct node
{
    int a, b, c, d, cnt, id;
} A[maxn], B[maxn], C[maxn];
int n, maxk, tot;
bool cmp(const node& x, const node& y)
{
    if (x.a != y.a) return x.a < y.a;
    if (x.b != y.b) return x.b < y.b;
    return x.c < y.c;
}
int ans[maxn];

void cdq2(int l, int r)
{
    if (l == r) return;
    int mid = l + r >> 1;
    cdq2(l, mid), cdq2(mid + 1, r);
    int p = l, q = mid + 1, k = l, sum = 0;
    while (p <= mid && q <= r)
    {
        if (B[p].c <= B[q].c)
        {
            sum += B[p].d;
            C[k++] = B[p++];
        }
        else
        {
            if (!B[q].d) ans[B[q].id] += sum;
            C[k++] = B[q++];
        }
    }
    while (p <= mid) C[k++] = B[p++];
    while (q <= r)
    {
        if (!B[q].d) ans[B[q].id] += sum;
        C[k++] = B[q++];
    }
    for (int i = l; i <= r; ++i) B[i] = C[i];
}
void cdq(int l, int r)
{
    if (l == r) return;
    int mid = l + r >> 1;
    cdq(l, mid), cdq(mid + 1, r);
    int p = l, q = mid + 1, k = l;
    while (p <= mid && q <= r)
    {
        if (A[p].b <= A[q].b)
        {
            A[p].d = A[p].cnt;
            B[k++] = A[p++];
        }
        else
        {
            A[q].d = 0;
            B[k++] = A[q++];
        }
    }
    while (p <= mid) A[p].d = A[p].cnt, B[k++] = A[p++];
    while (q <= r) A[q].d = 0, B[k++] = A[q++];
    for (int i = l; i <= r; ++i) A[i] = B[i];
    cdq2(l, r);
}
int d[maxn];
int main()
{
    read(n), read(maxk);
    for (int i = 1; i <= n; ++i) read(B[i].a), read(B[i].b), read(B[i].c), B[i].cnt = 1, B[i].id = i;
    std::sort(B + 1, B + 1 + n, cmp);
    for (int i = 1; i <= n; ++i)
    {
        if (B[i].a == B[i + 1].a && B[i].b == B[i + 1].b && B[i].c == B[i + 1].c)
            B[i + 1].cnt += B[i].cnt;
        else
            A[++tot] = B[i];
    }
    cdq(1, tot);
    for (int i = 1; i <= tot; ++i) d[ans[A[i].id] + A[i].cnt] += A[i].cnt;
    for (int i = 1; i <= n; ++i) printf("%d\n", d[i]);
    return 0;
}