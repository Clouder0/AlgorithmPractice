#include <cstdio>
#include <algorithm>
#include <set>
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
	for(; isdigit(c); c = nc()) r = r * 10 + c - 48;
	return r;
}
const int maxn = 3e5 + 100;
int n, m, q;
int cnt[maxn],root[maxn], sum[maxn * 20], L[maxn * 20], R[maxn * 20], ind;
long long val[maxn * 20];
inline int get(int l,int r,int p)
{
	if(p == n + 1) return r <= n ? r - l + 1 : (l <= n ? n - l + 1 : 0);
	return r < m ? r - l + 1 : (l < m ? m - l : 0);
}
long long ask(int askroot,int l,int r,int &p, int pos)
{
	if(!p) p = ++ind;
	sum[p]++;
	if(l == r) return val[p] ? val[p] : val[p] = (askroot == n + 1) ? 1ll * l * m : 1ll * m * (askroot-1) + l;
	int mid = l + r >> 1,lsum = get(l,mid,askroot) - sum[L[p]];
	return pos <= lsum ? ask(askroot,l,mid,L[p],pos) : ask(askroot,mid + 1,r,R[p],pos - lsum);
}
void modify(int askroot,int l,int r,int &p, int pos, long long k)
{
	if(!p) p = ++ind;
	--sum[p];
	if(l == r) return (void)(val[p] = k);
	int mid = l + r >> 1;
	if(pos <= mid) modify(askroot,l,mid,L[p],pos,k); else modify(askroot,mid + 1,r,R[p],pos,k);
}
int main()
{
	read(n), read(m), read(q);
	int maxx = std::max(n,m) + q + 10;
	for(int i = 1,x,y;i<=q;++i) 
	{
		static long long res;
		read(x),read(y);
		if(y == m) 
		{
			res = ask(n + 1, 1, maxx, root[n + 1], x);
			printf("%lld\n",res);
			modify(n + 1, 1, maxx, root[n + 1], n + (++cnt[n + 1]), res);
		}
		else 
		{
			res = ask(x, 1, maxx, root[x], y);
			printf("%lld\n", res);
			modify(n + 1, 1, maxx, root[n + 1], n + (++cnt[n + 1]), res);
			res = ask(n + 1,1,maxx,root[n + 1],x);
			modify(x, 1, maxx,root[x],m - 1 + (++cnt[x]), res);
		}
	}
	
	return 0;
}
