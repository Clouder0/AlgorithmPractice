#include <cstdio>
#include <vector>
#include <algorithm>
#include <cctype>
using namespace std;
const int bufSize = 1e6;
inline char nc()
{
	return getchar();
	static char buf[bufSize],*p1 = buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,bufSize,stdin),p1==p2)?EOF:*p1++;
}
template<typename T>
inline T read(T &r)
{
	static char c;
	static int flag;
	r = 0,flag = 1;
	for(c=nc();!isdigit(c);c=nc()) if(c == '-') flag = -1;
	for(;isdigit(c);c=nc()) r=r*10+c-48;
	return r*=flag;
}
const int maxn = 1e6 + 100;
int n,S[maxn],a[maxn],head[maxn],minval;
vector<int> V[maxn];
void solve(int l,int r,int dep)
{
	if(l > r) return;
	int tail = head[dep];
	while(V[dep][tail + 1] <= r) ++tail;
	for(int i = tail;i>=head[dep];--i) a[V[dep][i]] = ++minval;
	if(l <= V[dep][head[dep]] - 1) solve(l,V[dep][head[dep]] - 1,dep + 1);
	for(int i = head[dep] + 1;i<=tail;++i) 
		if(V[dep][i-1] + 1 <= V[dep][i] - 1) 
			solve(V[dep][i-1] + 1,V[dep][i] - 1,dep + 1);
	if(V[dep][tail] + 1 <= r) solve(V[dep][tail] + 1,r,dep + 1);
	head[dep] = tail + 1;
}
int main()
{
	read(n);
	for(int i = 1;i<=n;++i) read(S[i]);
	for(int i = 1;i<=n;++i) if(S[i] == -1) S[i] = S[i-1] + 1;
	for(int i = 1;i<=n;++i) V[i].push_back(0),head[i] = 1;
	for(int i = 1;i<=n;++i) V[S[i]].push_back(i);
	for(int i = 1;i<=n;++i) V[i].push_back(n + 1);
	solve(1,n,1);
	for(int i = 1;i<=n;++i) printf("%d ",a[i]);
	return 0;
}
