#include <cstdio>
#include <cmath>
using namespace std;
const int maxn = 500;
int n,s,t,A,B,cost[maxn];
int Px[maxn],Py[maxn];
double dis[maxn][maxn];
double getdis(int x1,int y1,int x2,int y2)
{
	return std::sqrt(1.0 * (x1-x2) * (x1-x2) + 1.0 * (y1-y2) * (y1-y2));
}
int main()
{
	scanf("%d",&n);
	while(n--)
	{
		scanf("%d %d %d %d",&s,&t,&A,&B);
		for(int i = 1;i<=4 * s;++i) for(int j = 1;j<=4*s;++j) dis[i][j] = 1e18;
		for(int i = 1;i<=s;++i)
		{
			
		}
	}
	return 0;
}
