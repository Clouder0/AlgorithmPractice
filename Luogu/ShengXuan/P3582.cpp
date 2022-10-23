#include <cstdio>
#include <cctype>
#include <algorithm>
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
	for(c=nc();!isdigit(c);c=nc());
	for(;isdigit(c);c=nc()) r=r*10+c-48;
	return r;
}
const int maxn = 1e6 + 100;
int n,m,a[maxn],w[maxn],last[maxn],vis[maxn];
long long maxx[maxn << 2],tag[maxn << 2];
#define ls p << 1
#define rs p << 1 | 1
inline void pushup(int p){maxx[p] = max(maxx[ls],maxx[rs]);}
inline void pushdown(int p)
{
	if(!tag[p]) return;
	maxx[ls] += tag[p],maxx[rs] += tag[p],tag[ls] += tag[p],tag[rs] += tag[p],tag[p] = 0;
}
void modify(int l,int r,int p,int ll,int rr,int k)
{
	if(l >= ll && r <= rr) return (void)(maxx[p] += k,tag[p] += k);
	int mid = (l + r) >> 1;
	pushdown(p);
	if(ll <= mid) modify(l,mid,ls,ll,rr,k); 
	if(rr > mid) modify(mid + 1,r,rs,ll,rr,k);
	pushup(p);
}
signed main()
{
	read(n),read(m);
	for(int i = 1;i<=n;++i) read(a[i]);
	for(int i = 1;i<=m;++i) read(w[i]);
	for(int i = n;i;--i) 
	{
		if(!vis[a[i]]) last[i] = n + 1;
		else last[i] = vis[a[i]];
		vis[a[i]] = i;
	}
	long long res = 0;
	for(int l = n;l;--l)
	{
		modify(1,n,1,l,last[l] - 1,w[a[l]]);
		if(last[l] <= n) modify(1,n,1,last[l],last[last[l]] - 1,-w[a[l]]);
		res = std::max(res,maxx[1]);
	}
	printf("%lld\n",res);
	return 0;
}
