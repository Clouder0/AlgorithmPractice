#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int A,B,C;
const double eps = 1e-8;
double f[110][110][110];
double dfs(int a,int b,int c)
{
	if(a == 100 || b == 100 || c == 100) return 0;
	if(fabs(f[a][b][c]) > eps) return f[a][b][c];
	int sum = a + b + c;
	return f[a][b][c] = 1.0 * a / sum * dfs(a + 1,b,c) + 1.0 * b / sum * dfs(a,b+1,c) + 1.0 * c / sum * dfs(a,b,c + 1) + 1.0;
}
int main()
{
	scanf("%d %d %d",&A,&B,&C);
	printf("%.8f\n",dfs(A,B,C));
	return 0;
}
