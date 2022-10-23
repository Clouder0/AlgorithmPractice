#include <cstdio>
#include <cstring>
using namespace std;
const int mod = 1000000007;
int T,n;
inline int add(int x,int y){int res = x + y;return res >= mod ? res - mod : res;}
inline int mul(int x,int y){return 1ll * x * y % mod;}
const int maxn = 10;
struct matrix
{
	int n,m,a[maxn][maxn];
	matrix(){memset(a,0,sizeof(a));}
	matrix operator*(const matrix &b)
	{
		matrix c;
		c.n = n,c.m = b.m;
		for(int i = 1;i<=n;++i) for(int j = 1;j<=m;++j) for(int k = 1;k<=b.m;++k) c.a[i][k] = add(c.a[i][k],mul(a[i][j],b.a[j][k]));
		return c;
	}
};
int f[4][3];
int main()
{
	scanf("%d",&T);
	f[1][0] = 1,f[1][1] = 1,f[2][0] = 2,f[2][1] = 1,f[3][0] = 3,f[3][1] = 3,f[3][2] = 2;
	while(T--)
	{
		scanf("%d",&n);
		if(n <= 3) {printf("%d\n",f[n][2]);continue;}
		matrix O;
		O.n = 1,O.m = 9;
		O.a[1][1] = f[1][0],O.a[1][2] = f[1][1],O.a[1][3] = f[1][2];
		O.a[1][4] = f[2][0],O.a[1][5] = f[2][1],O.a[1][6] = f[2][2];
		O.a[1][7] = f[3][0],O.a[1][8] = f[3][1],O.a[1][9] = f[3][2];
		matrix P;
		P.n = 9,P.m = 9;
		P.a[2][9] = 2,P.a[4][1] = 1,P.a[4][7] = 1,P.a[5][2] = 1,P.a[5][8] = 1,P.a[5][9] = 2,P.a[6][3] = 1,P.a[6][9] = 1;
		P.a[7][4] = P.a[7][7] = P.a[7][8] = 1,P.a[8][5] = 1,P.a[9][6] = P.a[9][9] = 1;
		n -= 3;
		while(n)
		{
			if(n & 1) O = O * P;
			P = P * P;
			n >>= 1;
		}
		printf("%d\n",O.a[1][9]);
	}
	return 0;
}
