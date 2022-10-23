#include <cstdio>
const int maxn = 1e5 + 100;
const int maxm = 1e6 + 100;
int n,m,a[maxn],vis[maxm],res;
int root[maxm],L[maxn * 20],R[maxn * 20],sum[maxn * 20],lval[maxn * 20],rval[maxn * 20],ind;
int s[maxn * 20],top;
inline int newnode(){return top > 0 ? s[top--] : ++ind;}
inline void del(int x){if(x) L[x] = R[x] = sum[x] = lval[x] = rval[x] = 0,s[++top] = x;}
inline void pushup(int p)
{
	sum[p] = sum[L[p]] + sum[R[p]],lval[p] = lval[L[p]],rval[p] = rval[R[p]];
	if(rval[L[p]] && lval[R[p]]) --sum[p];

}
void modify(int l,int r,int &p,int pos)
{
	if(!p) p = newnode();
	if(l == r) return (void)(lval[p] = rval[p] = sum[p] = 1);
	int mid = (l + r) >> 1;
	if(pos <= mid) modify(l,mid,L[p],pos); else modify(mid + 1,r,R[p],pos);
	pushup(p);
}
void merge(int &x,int y)
{
	if(!x || !y) return (void)(x += y);
	merge(L[x],L[y]),merge(R[x],R[y]),pushup(x),del(y);
}
int main()
{
	scanf("%d %d",&n,&m);
	for(int i = 1;i<=n;++i) scanf("%d",a + i),modify(1,n,root[a[i]],i);
	for(int i = 1;i<=n;++i) if(!vis[a[i]]) res += sum[root[a[i]]],vis[a[i]] = 1;
	for(int i = 1,opt,x,y;i<=m;++i)
	{
		scanf("%d",&opt);
		if(opt == 1)
		{
			scanf("%d %d",&x,&y);
			if(x == y) continue;
			res -= sum[root[x]] + sum[root[y]];
			merge(root[y],root[x]),root[x] = newnode();
			res += sum[root[y]];
		}
		else printf("%d\n",res);
	}
	return 0;
}
