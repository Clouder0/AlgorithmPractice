#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
#include <cctype>
using namespace std;
const int bufSize = 1e6;
#define DEBUG
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
const int maxn = 2e5 + 100;
int n,fa[maxn],w[maxn];
struct node
{
	int to,next;
}E[maxn];
int head[maxn],tot;
inline void add(int x,int y){E[++tot].next = head[x],head[x] = tot,E[tot].to = y;}
priority_queue<int> S[maxn];
void dfs(int u)
{
	vector<int> more;
	for(int p = head[u];p;p=E[p].next)
	{
		int v = E[p].to;
		dfs(v);
		if(S[u].size() < S[v].size()) std::swap(S[u],S[v]);
		while(!S[v].empty())
			more.push_back(std::max(S[u].top(),S[v].top())),S[u].pop(),S[v].pop();
		for(vector<int>::iterator it = more.begin();it!=more.end();++it) S[u].push(*it);
		more.clear();
	}
	S[u].push(w[u]);
	vector<int>().swap(more);
}
int main()
{
	read(n);
	for(int i = 1;i<=n;++i) read(w[i]);
	for(int i = 2;i<=n;++i) read(fa[i]),add(fa[i],i);
	dfs(1);
	long long res = 0;
	while(!S[1].empty()) res += S[1].top(),S[1].pop();
	printf("%lld\n",res);
	return 0;
}
