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
	for(c=nc();!isdigit(c);c=nc());
	for(;isdigit(c);c=nc()) r=r*10+c-48;
	return r;
}
const int maxn = 5e5 + 100;
const int mod = 998244353;
inline int add(int x,int y){int res = x + y;return res >= mod ? res - mod : res;}
inline int mul(int x,int y)
{
	long long res = 1ll * x * y;
	return res >= mod ? res % mod : res;
}
struct node
{
	int l,r,x;
}A[maxn];
int n,m,k,lim[maxn],f[maxn],d[maxn];
int main()
{
	read(n),read(k),read(m);
	for(int i = 1;i<=m;++i) read(A[i].l),read(A[i].r),read(A[i].x);
	int res = 1;
	for(int bit = 0;bit < k;++bit)
	{
		for(int i = 1;i<=n + 1;++i) d[i] = lim[i] = f[i] = 0;
		for(int i = 1;i<=m;++i) 
			if((A[i].x >> bit) & 1) d[A[i].l]++,d[A[i].r+1]--;
			else lim[A[i].r] = max(lim[A[i].r],A[i].l);
		for(int i = 2;i<=n + 1;++i) d[i] += d[i-1], lim[i] = max(lim[i],lim[i-1]);
		f[0] = 1;
		int p = 0,sum = f[0];
		for(int i = 1;i<=n + 1;++i)
		{
			if(!d[i]) f[i] = sum,sum = add(sum,f[i]);
			while(p < lim[i]) sum = add(sum,mod - f[p++]);
		}
		//printf("%d %d\n",bit,f[n+1]);
		res = mul(res,f[n+1]);
	}
	printf("%d\n",res);
	return 0;
}
