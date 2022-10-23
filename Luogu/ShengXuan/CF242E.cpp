#include <cstdio>
#include <algorithm>
#include <cctype>
using namespace std;
const int bufSize = 1e6;
inline char nc()
{
	#ifdef DEBUG
	return getchar();
	#endif
	static char buf[bufSize],*p1 = buf,*p2 = buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,bufSize,stdin),p1==p2)?EOF:*p1++;
}
template<typename T>
inline T read(T &r)
{
	static char c;
	r = 0;
	for(c = nc(); !isdigit(c); c = nc());
	for(; isdigit(c); c = nc()) r = r*10 + c - 48;
	return r;
}
const int maxn = 1e5 + 100;
int n, m, a[maxn];
struct node
{
	int sum, rev, len;
}A[maxn << 2][20];
#define lson p << 1
#define rson p << 1 | 1
inline void pushup(node &now, node &ls, node &rs) { now.sum = ls.sum + rs.sum; }
inline void pushdown(node &now, node &ls, node &rs)
{
	if(!now.rev) return;
	ls.sum = ls.len - ls.sum, rs.sum = rs.len - rs.sum, ls.rev ^= 1, rs.rev ^= 1, now.rev = 0;
}
void build(int l,int r,int p)
{
	for(int i = 0;i < 20;++i) A[p][i].len = r - l + 1;
	if(l == r)
	{
		for(int i = 0; (1 << i) <= a[l]; ++i) A[p][i].sum = (a[l] >> i) & 1;
		return;
	}
	int mid = l + r >> 1;
	build(l, mid, lson),build(mid + 1, r, rson);
	for(int i = 0; i < 20; ++i) pushup(A[p][i], A[lson][i], A[rson][i]);
}
int ask(int l, int r, int p, int ll, int rr, int bit)
{
	if(A[p][bit].sum == 0) return 0;
	if(l >= ll && r <= rr) return A[p][bit].sum;
	int mid = l + r >> 1,res = 0;
	pushdown(A[p][bit], A[lson][bit], A[rson][bit]);
	if(ll <= mid) res = ask(l, mid, lson, ll, rr, bit);
	if(rr > mid) res += ask(mid + 1, r, rson, ll, rr, bit);
	return res;
}
int qbit[30], cnt;
void modify(int l, int r, int p, int ll, int rr)
{
	if(l >= ll && r <= rr)
	{
		for(int i = 1; i <= cnt; ++i) A[p][qbit[i]].sum = r - l + 1 - A[p][qbit[i]].sum, A[p][qbit[i]].rev ^= 1;
		return;
	}
	int mid = l + r >> 1;
	for(int i = 1; i <= cnt; ++i) pushdown(A[p][qbit[i]],A[lson][qbit[i]],A[rson][qbit[i]]);
	if(ll <= mid) modify(l, mid, lson, ll, rr);
	if(rr > mid) modify(mid + 1, r, rson , ll, rr);
	for(int i = 1; i <= cnt; ++i) pushup(A[p][qbit[i]], A[lson][qbit[i]], A[rson][qbit[i]]);
}
int main()
{
	read(n);
	for(int i = 1; i <= n; ++i) read(a[i]);
	build(1, n, 1);
	read(m);
	for(int i = 1, opt, l, r, x; i <= m; ++i) 
	{
		read(opt), read(l), read(r);
		if(opt == 1)
		{
			long long res = 0;
			for(int j = 0; j < 20; ++j) res += (1ll << j) * ask(1, n, 1, l, r, j);
			printf("%lld\n", res);
		}
		else
		{
			read(x);
			cnt = 0;
			for(int j = 0; j < 20; ++j) if(x & (1 << j)) qbit[++cnt] = j;
			modify(1, n, 1, l, r);
		}
	}
	return 0;
}
