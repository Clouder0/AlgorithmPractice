#include <cstdio>
#include <algorithm>
#include <cctype>
using namespace std;
const int bufSize = 1e6;
inline char nc()
{
	static char buf[bufSize],*p1 = buf,*p2 = buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,bufSize,stdin),p1==p2)?EOF:*p1++;
}
template<typename T>
inline T read(T &r)
{
	static char c;
	r = 0;
	for(c=nc();!isdigit(c);c=nc());
	for(;isdigit(c);c=nc()) r = r * 10 + c - 48;
	return r;
}
const int maxn = 2e6 + 100;
int n,H[maxn],cnt;
struct node
{
	int opt,x,y;
}A[maxn];
int sum1[maxn],sum2[maxn];
inline void add1(int x,int k){for(;x<=cnt;x+=x&-x) sum1[x] += k;}
inline void add2(int x,int k){for(;x>0;x-=x&-x) sum2[x] += k;}
int main()
{
	read(n);
	for(int i = 1,opt,k;i<=n;++i)
	{
		read(opt);
		if(opt == 1) read(A[i].opt),read(A[i].x),read(A[i].y),H[++cnt] = A[i].x;
		else read(k),A[i] = A[k],A[i].y = -A[i].y;
	}
	sort(H + 1,H + 1 + cnt),cnt = unique(H + 1,H + 1 + cnt) - H - 1;
	for(int i = 1;i<=n;++i) A[i].x = lower_bonud(H + 1, H + 1 + cnt) - H - 1;
	int presum = 0,sufsum = 0;
	for(int i = 1;i<=n;++i)
	{
		int now = 0,res1 = 0,res2 = sufsum;
		int ans = 0,anst = 0;
		for(int j = 21;j>=0;--j) 
		{
			int p = now ^ (1 << j);
			if(p > cnt) continue;
			if(res1 + sum1[p] < res2 - sum2[p]) res1 += sum1[p],res2 -= sum2[p],now = p;
		}
		ans = min(res1,res2),anst = now;
		now = ans,res1 = presum,res2 = 0;
		for(int j = 0;j<=21;++j)
		{
			int p = now ^ (1 << j);
			if(res1 - sum1[p]
		}
	}
	return 0;
}
