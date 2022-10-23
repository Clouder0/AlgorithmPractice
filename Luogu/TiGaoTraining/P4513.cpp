#include <cstdio>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
using namespace std;
inline char nc()
{
	#ifdef DEBUG
	return getchar();
	#endif
	static char buf[bufSize], *p1 = buf, *p2 = buf;
	return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
template<typename T>
inline T read(T &r)
{
	static char c;
	static int flag;
	flag = 1, r = 0;
	for (c = nc(); !isdigit(c); c = nc()) if (c == '-') flag = -1;
	for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
	return r *= flag;
}
const int maxn = 5e5 + 100;
struct node
{
    int lmax, rmax, maxx, sum;
    node() { lmax = rmax = maxx = sum = -1 << 30; }
} A[maxn << 2];
int n, m, a[maxn];
#define ls p << 1
#define rs p << 1 | 1
inline void pushup(node& now, node& l, node& r)
{
    now.sum = l.sum + r.sum;
    now.maxx = max(l.maxx, r.maxx);
    now.maxx = max(now.maxx, l.rmax + r.lmax);
    now.lmax = max(l.lmax, l.sum + r.lmax);
    now.rmax = max(r.rmax, r.sum + l.rmax);
}
void build(int l, int r, int p)
{
    if (l == r) return (void)(A[p].lmax = A[p].rmax = A[p].maxx = A[p].sum = a[l]);
    int mid = l + r >> 1;
    build(l, mid, ls), build(mid + 1, r, rs), pushup(A[p], A[ls], A[rs]);
}
node ask(int l, int r, int p, int ll, int rr)
{
    if (l >= ll && r <= rr) return A[p];
    int mid = l + r >> 1;
    if (ll <= mid && rr > mid)
    {
        node lres = ask(l, mid, ls, ll, rr), rres = ask(mid + 1, r, rs, ll, rr), res;
        pushup(res, lres, rres);
        return res;
    }
    if (ll <= mid) return ask(l, mid, ls, ll, rr);
    return ask(mid + 1, r, rs, ll, rr);
}
void modify(int l, int r, int p, int pos, int k)
{
    if (l == r) return (void)(A[p].lmax = A[p].rmax = A[p].maxx = A[p].sum = k);
    int mid = l + r >> 1;
    if (pos <= mid) modify(l, mid, ls, pos, k);
    else modify(mid + 1, r, rs, pos, k);
    pushup(A[p], A[ls], A[rs]);
}
int main()
{
    read(n), read(m);
    for (int i = 1; i <= n; ++i) read(a[i]);
    build(1, n, 1);
    for (int i = 1, opt, l, r; i <= m; ++i)
    {
        read(opt), read(l), read(r);
        if (opt == 1)
        {
        	if(l > r) std::swap(l,r);
            node t = ask(1, n, 1, l, r);
            printf("%d\n", t.maxx);
        }
        else modify(1, n, 1, l, r);
    }
    return 0;
}
