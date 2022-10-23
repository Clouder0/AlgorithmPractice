#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 200;
long long k;
inline long long add(long long x,long long y)
{
	if(x == -1 || y == -1) return -1;
	long long res = x + y;
	return res > k ? -1 : res;
}
inline long long mul(long long x,long long y)
{
	if(x == 0 || y == 0) return 0;
	if(x == -1 || y == -1) return -1;
	long long res = x * y;
	return res > k ? -1 : res;
}
struct matrix
{
	int n,m;
	long long a[maxn][maxn];
	matrix(){memset(a,0,sizeof(a));}
	matrix operator*(const matrix &b)
	{
		matrix c;
		c.n = n,c.m = b.m;
		for(int i = 1;i<=n;++i) for(int j = 1;j<=m;++j) for(int k = 1;k<=b.m;++k)
			c.a[i][k] = add(c.a[i][k],mul(a[i][j],b.a[j][k]));
		return c;
	}
	void output()
	{
		puts("");
		for(int i = 1;i<=n;puts(""),++i) for(int j = 1;j<=m;++j) printf("%lld ",a[i][j]);
		puts("");
	}
}A[100];
int n,m,id[maxn][4],ind;
int main()
{
	scanf("%d %d %lld",&n,&m,&k);
	for(int i = 1;i<=n;++i) for(int j = 1;j<=3;++j) id[i][j] = ++ind;
	++ind;//sum point
	A[0].n = ind,A[0].m = ind;
	for(int i = 1;i<=n;++i) for(int j = 2;j<=3;++j) A[0].a[id[i][j]][id[i][j-1]] = 1;
	for(int i = 1;i<=n;++i) A[0].a[id[i][1]][ind] = 1;
	A[0].a[ind][ind] = 1;
	for(int i = 1,a,b,c;i<=m;++i)
	{
		scanf("%d %d %d",&a,&b,&c);
		A[0].a[id[a][1]][id[b][c]] += 1;
	}
	int maxlog = 1;
	matrix S;
	S.n = 1,S.m = ind;
	for(int i = 1;i<=n;++i) S.a[1][id[i][1]] = 1;
	S.a[1][ind] = -n;
	for(;;++maxlog)
	{
		A[maxlog] = A[maxlog-1] * A[maxlog-1];
		matrix T = S * A[maxlog];
		long long sum = T.a[1][ind];
		if(sum == -1) break;
		for(int j = 1;j<=n;++j) sum = add(sum,T.a[1][id[j][1]]);
		if(sum == -1) break;
		if(maxlog > 70){puts("-1");return 0;}
	}
	//A[0].output(),A[1].output();
	long long res = 0;
	for(int i = maxlog;i >= 0;--i)
	{
		matrix T = S * A[i];
		long long sum = T.a[1][ind];
		if(sum == -1) continue;
		for(int j = 1;j<=n;++j) sum = add(sum,T.a[1][id[j][1]]);
		if(sum == -1) continue;
		if(sum < k) res |= 1ll << i,S = T;
		//printf("%d %lld\n",i,sum);
		//if(sum == -1) continue;
		
	}
	//S.output();
	printf("%lld\n",res + 1);
	return 0;
}
