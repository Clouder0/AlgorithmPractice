#include <cstdio>
#include <algorithm>
#include <ctype.h>
using namespace std;
const int bufSize = 1e6;
inline char nc()
{
	#ifdef DEBUG
	return getchar();
	#endif
	static char buf[bufSize],*p1=buf,*p2=buf;
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
const int maxn = 2e6 + 100;
int n,c,m,a[maxn],last[maxn],secl[maxn],ANS[maxn];
struct node
{
	int id,x,next;	
}A[maxn];
int head[maxn];
inline void add(int pos,int x,int id)
{
	static int tot = 0;
	A[++tot].next = head[pos],head[pos] = tot,A[tot].x = x,A[tot].id = id;
}
int sum[maxn];
inline void add(int x, int k){ for(; x <= n; x += x & -x) sum[x] += k; }
inline int ask(int x){ int res = 0; for(; x > 0; x -= x & -x) res += sum[x]; return res; }
int main()
{
	read(n),read(c),read(m);
	for(int i = 1;i<=n;++i) read(a[i]);
	for(int i = 1,l,r;i<=m;++i) read(l),read(r),add(r,l,i);
	for(int i = 1;i<=n;++i)
	{
		if(secl[a[i]]) add(secl[a[i]],-1);
		if(last[a[i]]) add(last[a[i]],1);
		secl[a[i]] = last[a[i]], last[a[i]] = i;
		for(int p = head[i];p;p=A[p].next) ANS[A[p].id] = ask(i) - ask(A[p].x - 1);
	}
	for(int i = 1;i<=m;++i) printf("%d\n",ANS[i]);
	return 0;
}
