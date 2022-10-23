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
struct node
{
	int to,next,val;
}E[maxn << 1];
int head[maxn],tot;
inline void add(int x,int y,int val){E[++tot].next = head[x],head[x] = tot,E[tot].to = y,E[tot].val = val;}
int n, m, fa[maxn][19], S[maxn], bel[maxn], tag[maxn], isleaf[maxn], can[maxn], more[maxn];
long long dis[maxn][19], wdis;
void dfs(int u)
{
	isleaf[u] = 1;
	for(int i = 1; i < 19; ++i) fa[u][i] = fa[fa[u][i-1]][i-1], dis[u][i] = dis[u][i-1] + dis[fa[u][i-1]][i-1];
	for(int p = head[u]; p; p = E[p].next)
	{
		int v = E[p].to;
		if(v == fa[u][0]) continue;
		bel[v] = bel[u], fa[v][0] = u, dis[v][0] = E[p].val, dfs(v),isleaf[u] = 0;
	}
}
void dfs1(int u)
{
	if(tag[u]) return;
	if(isleaf[u]) return (void)(can[bel[u]] = 0);
	for(int p = head[u];p;p=E[p].next)
	{
		int v = E[p].to;
		if(v == fa[u][0]) continue;
		dfs1(v);
	}
}
multiset<long long> s[maxn];
bool check()
{
	//printf("\nbegin:%lld\n",wdis);
	for(int i = 1;i <= n;++i) more[i] = tag[i] = can[i] = 0,s[i].clear();
	multiset<long long> A;
	for (int i = 1; i <= m; ++i) 
	{
		long long left = wdis;
		int u = S[i], belu = bel[u];
		for(int j = 18; u != 1 && j >= 0; --j) 
			if(left - dis[u][j] >= 0) 
				left -= dis[u][j], u = fa[u][j];
		if(u == 1) s[belu].insert(left), more[belu] = 1,A.insert(left);//, printf("top:%d %lld\n",belu,left);
		else tag[u] |= 1;
	}
	
	for(int p = head[1];p;p=E[p].next)
	{
		int v = E[p].to;
		can[v] = 1;
		if(more[v])
		{
			dfs1(v);
			if(!can[v] && *s[v].begin() <= dis[v][0]) can[v] = 1, A.erase(A.find(*s[v].begin()));
			
		}
		else dfs1(v);
	}
	for(int p = head[1];p;p=E[p].next)
	{
		int v = E[p].to, d = dis[v][0];
		if(!can[v]) 
		{
			set<long long>::iterator it = A.lower_bound(d);
			if(it == A.end()) return 0;
			//printf("need: %d %lld\n",v,*it);
			A.erase(it);
		}
	}
	return 1;
}
int main()
{
	read(n);
	for(int i = 1, u, v, w; i < n; ++i) read(u), read(v), read(w), add(u, v, w), add(v, u, w);
	read(m);
	for(int i = 1; i <= m; ++i) read(S[i]);
	for(int i = 0;i < 19;++i) fa[1][i] = 1,dis[1][i] = 0;
	for(int p = head[1];p;p=E[p].next) 
	{
		int v = E[p].to;
		bel[v] = v, fa[v][0] = 1, dis[v][0] = E[p].val, dfs(v);
	}
	long long maxdis = 0;
	for(int i = 1; i <= n; ++i) maxdis = std::max(maxdis, dis[i][23]);
	long long l = 0, r = maxdis << 1,ans = -1;
	while(l <= r)
	{
		wdis = (l + r) >> 1;
		if(check()) r = wdis - 1,ans = wdis;
		else l = wdis + 1;
	}
	printf("%lld\n",ans);
	return 0;
}
