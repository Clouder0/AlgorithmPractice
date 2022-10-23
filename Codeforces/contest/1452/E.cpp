#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 2100;
int n,m,k,prefix[maxn],suffix[maxn],pos[maxn];
struct node
{
	int l,r;
}A[maxn];
bool cmp(const node &a,const node &b)
{
	return a.l + a.r < b.l + b.r;
}
int main()
{
	scanf("%d %d %d",&n,&m,&k);
	for(int i = 1;i<=m;++i) scanf("%d %d",&A[i].l,&A[i].r);
	if(m == 1) return printf("%d\n",min(k,A[1].r - A[1].l + 1)),0;
	sort(A + 1,A + 1 + m,cmp);
	for(int i = 1; i <= m; ++i)
	{
		for(int j = 1; j + k - 1 <= n; ++j)
		{
			int l = max(A[i].l,j),r = min(A[i].r,j + k - 1);
			if(l <= r) pos[j] += r - l + 1;
			prefix[i] = max(prefix[i],pos[j]);
		}
	}
	for(int i = 1;i<=n;++i) pos[i] = 0;
	for(int i = m;i;--i)
	{
		for(int j = 1;j + k - 1 <= n;++j)
		{
			int l = max(A[i].l,j),r = min(A[i].r,j + k - 1);
			if(l <= r) pos[j] += r - l + 1;
			suffix[i] = max(suffix[i],pos[j]);
		}
	}
	int res = 0;
	for(int i = 1;i<m;++i) res = max(res,prefix[i] + suffix[i + 1]);
	printf("%d\n",res);
	return 0;
}
