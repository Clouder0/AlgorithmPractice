#include <cstdio>
#include <algorithm>
#include <cctype>
using namespace std;
const int bufSize = 1e6;
//#define DEBUG
inline char nc()
{
	#ifdef DEBUG
	return getchar();
	#endif
	static char buf[bufSize],*p1 = buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,bufSize,stdin),p1==p2)?EOF:*p1++;
}
template<typename T>
inline T read(T &r)
{
	static char c;
	r = 0;
	for(c=nc();!isdigit(c);c=nc());
	for(;isdigit(c);c=nc()) r = r*10+c-48;
	return r;
}
const int maxn = 1e5 + 100;
struct node
{
	int to,next;
}E[maxn << 1];
int head[maxn],tot;
inline void add(int x,int y){E[++tot].next = head[x],head[x] = tot,E[tot].to = y;}
int n;
int nowk,num,f[maxn];
void dfs(int u,int fa)
{
	int maxx = 0,secx = 0;
	for(int p = head[u];p;p=E[p].next)
	{
		int v = E[p].to;
		if(v == fa) continue;
		dfs(v,u);
		if(f[v] > maxx) secx = maxx,maxx = f[v];
		else if(f[v] > secx) secx = f[v];
	}
	if(maxx + secx + 1 >= nowk) ++num,f[u] = 0;
	else f[u] = maxx + 1;
}
inline int get(int x)
{
	num = 0,nowk = x,dfs(1,0);
	return num;
}
int ANS[maxn];
void solve(int l,int r,int L,int R)
{
	r = min(r,n / L);
	if(l > r || L > R) return;
	if(l == r)
	{
		for(int i = L;i<=R;++i) ANS[i] = l;
		return;
	}
	int mid = (L + R) >> 1,res = get(mid);
	ANS[mid] = res;
	solve(res,r,L,mid - 1),solve(l,res,mid + 1,R);
}
int main()
{
	read(n);
	for(int i = 1,a,b;i<n;++i) read(a),read(b),add(a,b),add(b,a);
	solve(0,n,1,n);
	for(int i = 1;i<=n;++i) printf("%d\n",ANS[i]);
	return 0;
}
