#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 110;
const int mod = 2009;
inline int add(int x,int y){int res = x + y;return res >= mod ? res - mod : res;}
inline int mul(int x,int y){return 1ll * x * y % mod;}
struct matrix
{
	int n,m;
	int a[maxn][maxn];
	matrix() {memset(a,0,sizeof(a));}
	matrix operator*(const matrix b)
	{
		matrix c;
		c.n = n,c.m = b.m;
		for(int i = 1;i<=n;++i) for(int j = 1;j<=m;++j) for(int k = 1;k<=b.m;++k) 
			c.a[i][k] = add(c.a[i][k],mul(a[i][j],b.a[j][k]));
		return c;
	}
};
int n,t,cnt,id[maxn][maxn];
matrix A,B;
char s[maxn];
int main()
{
	scanf("%d %d",&n,&t);
	for(int i = 1;i<=n;++i) for(int j = 1;j<=9;++j) id[i][j] = ++cnt;
	for(int i = 1;i<=n;++i) for(int j = 2;j<=9;++j) B.a[id[i][j]][id[i][j-1]] = 1;
	for(int i = 1;i<=n;++i)
	{
		scanf("%s",s + 1);
		for(int j = 1;j<=n;++j) 
			if(s[j] != '0')
			{
				int d = s[j] - '0';
				B.a[id[i][1]][id[j][d]] = 1;
			}
	}
	
	A.n = 1,A.m = cnt,B.n = B.m = cnt;
	A.a[1][id[1][1]] = 1;
	for(;t;t >>= 1)
	{
		if(t & 1) A = A * B;
		B = B * B;
	}
	printf("%d\n",A.a[1][id[n][1]]);
	return 0;
}
