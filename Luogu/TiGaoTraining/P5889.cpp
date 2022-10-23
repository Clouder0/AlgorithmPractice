#include <cstdio>
#include <algorithm>
#include <ctype.h>
const int bufSize = 2e6;
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
	r = 0;
	for (c = nc(); !isdigit(c); c = nc());
	for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
	return r;
}
const int maxn = 5e5 + 100;
int n, m, q, opt[maxn];
struct node
{
    int up, len;
    long long val;
} A[maxn << 2];
#define ls p << 1
#define rs p << 1 | 1
inline void pushup(node& now, node& l, node& r)
{
    if (l.len > r.up) now.up = l.up, now.len = l.len - r.up + r.len, now.val = ((l.val >> r.up) << r.len) | r.val;
    else now.up = l.up + r.up - l.len, now.len = r.len, now.val = r.val;
}
void build(int l,int r,int p)
{
	if(l == r)
	{
        if (opt[l] == 1) A[p].len = 1;
        else if (opt[l] == 2) A[p].len = 1, A[p].val = 1;
        else A[p].up = 1;
        return;
	}
	int mid = l + r >> 1;
    build(l, mid, ls), build(mid + 1, r, rs), pushup(A[p], A[ls], A[rs]);
}
node ask(int l, int r, int p, int ll, int rr)
{
    if (l >= ll && r <= rr) return A[p];
    int mid = l + r >> 1;
    if (ll <= mid && rr > mid)
    {
        node lans = ask(l, mid, ls, ll, rr), rans = ask(mid + 1, r, rs, ll, rr), ans;
        pushup(ans, lans, rans);
        return ans;
    }
    if (ll <= mid) return ask(l, mid, ls, ll, rr);
    return ask(mid + 1, r, rs, ll, rr);
}
void modify(int l, int r, int p, int pos)
{
    if (l == r)
    {
        if (opt[l] == 1) A[p].len = 1, A[p].val = 0, A[p].up = 0;
        else if (opt[l] == 2) A[p].len = 1, A[p].val = 1, A[p].up = 0;
        else A[p].up = 1, A[p].len = 0, A[p].val = 0;
        return;
    }
	int mid = l + r >> 1;
    if (pos <= mid) modify(l, mid, ls, pos);
    else modify(mid + 1, r, rs, pos);
    pushup(A[p],A[ls],A[rs]);
}
int main()
{
    read(n), read(m), read(q);
	for (int i = 1; i <= m; ++i) read(opt[i]);
    build(1, m, 1);
    for (int i = 1, type, l, r; i <= q; ++i)
    {
		read(type);
		if(type == 1)
		{
            long long s;
            read(s), read(l), read(r);
            node t = ask(1, m, 1, l, r);
            printf("%lld\n", (std::max(1ll, s >> t.up) << t.len) + t.val);
        }
        else read(l), read(r), opt[l] = r, modify(1, m, 1, l);
    }
    return 0;
}