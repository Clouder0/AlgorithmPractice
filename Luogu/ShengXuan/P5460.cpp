#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn = 1e5 + 100;
int n,m;
int opt[maxn],ANS[maxn];
char opts[maxn][34], query[maxn][34];
vector<int> add[maxn],del[maxn];
int son[maxn * 33][2],cnt[maxn * 33],ed[maxn * 33],tag[maxn * 33],ind;
inline void pushdown(int x)
{
	if(!son[x][0]) son[x][0] = ++ind;
	if(!son[x][1]) son[x][1] = ++ind;
	if(!tag[x]) return;
	if(!ed[son[x][0]]) cnt[son[x][0]] += tag[x],tag[son[x][0]] += tag[x];
	if(!ed[son[x][1]]) cnt[son[x][1]] += tag[x],tag[son[x][1]] += tag[x];
	tag[x] = 0;
}
void modify(char *s,int val)
{
	int u = 0;
	for(;*s != '\0';++s) pushdown(u), u = son[u][*s - '0'];
	ed[u] += val,tag[u]++,cnt[u]++;
}
int ask(char *s)
{
	int u = 0;
	for(;*s != '\0';++s) pushdown(u),u = son[u][*s - '0'];
	return cnt[u];
}
int main()
{
	scanf("%d %d",&n,&m);
	for(int i = 1;i<=n;++i)
	{
		static char t[10];
		scanf("%s %s",t,opts[i] + 1);
		if(t[0] == 'A') opt[i] = 1; else opt[i] = -1;
	}
	for(int i = 1,a,b;i<=m;++i)
	{
		scanf("%s %d %d",query[i] + 1,&a,&b);
		del[a].push_back(i),add[b].push_back(i);
	}
	for(int i = 1;i<=n;++i)
	{
		modify(opts[i] + 1,opt[i]);
		for(vector<int>::iterator it = add[i].begin();it!=add[i].end();++it) ANS[*it] += ask(query[*it] + 1);
		for(vector<int>::iterator it = del[i].begin();it!=del[i].end();++it) ANS[*it] -= ask(query[*it] + 1);
	}
	for(int i = 1;i<=m;++i) printf("%d\n",ANS[i]);
	return 0;
}
