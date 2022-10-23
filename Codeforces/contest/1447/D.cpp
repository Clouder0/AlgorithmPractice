#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 5100;
char A[maxn],B[maxn];
int n,m,f[maxn][maxn];
int main()
{
	scanf("%d %d",&n,&m);
	scanf("%s\n%s",A + 1,B + 1);
	int res = 0;
	for(int i = 1;i<=n;++i) for(int j = 1;j<=m;++j)
	{
		if(A[i] == B[j]) f[i][j] = f[i-1][j-1] + 2;
		f[i][j] = max(f[i][j],max(0,max(f[i-1][j],f[i][j-1])) - 1);
		res = max(res,f[i][j]);
	}
	printf("%d\n",res);
	return 0;
}
