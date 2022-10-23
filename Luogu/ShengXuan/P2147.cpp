#include <cstdio>
#include <algorithm>
#define ls son[x][0]
#define rs son[x][1]
const int maxn = 2e5 + 100;
int n,m,son[maxn][2],fa[maxn],rev[maxn];
inline void pushdown(int x) { if(rev[x]) std::swap(ls,rs),rev[ls] ^= 1,rev[rs] ^= 1,rev[x] = 0; }
inline int get(int x){return son[fa[x]][1] == x;}
inline int isroot(int x){return son[fa[x]][0] != x && son[fa[x]][1] != x;}
void rotate(int x)
{
	int f = fa[x],ff = fa[f], k = get(x);
	if(!isroot(f)) son[ff][get(f)] = x;
	fa[son[x][k^1]] = f,son[f][k] = son[x][k^1];
	son[x][k^1] = f,fa[f] = x,fa[x] = ff;
}
void update(int x){if(!isroot(x)) update(fa[x]); pushdown(x);}
void splay(int x)
{
	update(x);
	for(int f = fa[x];!isroot(x);rotate(x),f = fa[x]) if(!isroot(f)) rotate(get(x) == get(f) ? f : x);
}
void access(int x) { for(int p = 0;x;p = x,x = fa[x]) splay(x),rs = p; } 
void makeroot(int x) { access(x),splay(x),rev[x] ^= 1;}
void link(int x,int y){makeroot(x),splay(x),fa[x] = y;}
void cut(int x,int y){makeroot(x),access(y),splay(y),fa[x] = son[y][0] = 0;}
int find(int x){access(x),splay(x);int p = x;while(son[p][0]) p = son[p][0]; return p;}
int main()
{
	scanf("%d %d",&n,&m);
	for(int i = 1,a,b;i<=m;++i)
	{
		static char s[10];
		scanf("%s %d %d",s + 1,&a,&b);
		if(s[1] == 'Q') puts(find(a) == find(b) ? "Yes" : "No");
		else if(s[1] == 'C') link(a,b);
		else cut(a,b);
	}
	return 0;
}
