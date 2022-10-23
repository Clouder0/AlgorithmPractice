#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 2e5 + 100;
int T,n;
struct node
{
	int a , b;
}A[maxn];
bool cmp(const node &x,const node &y){return x.a < y.a;}
long long sufsum[maxn];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		for(int i = 1;i<=n;++i) scanf("%d",&A[i].a);
		for(int i = 1;i<=n;++i) scanf("%d",&A[i].b);
		sort(A + 1,A + 1 + n,cmp);
		sufsum[n + 1] = 0;
		for(int i = n;i;--i) sufsum[i] = sufsum[i + 1] + A[i].b;
		int p = n + 1, res = A[n].a,now = 0;
		int bsum = 0;
		for(int i = 1;bsum < res && i<=n;++i) bsum += A[i].b;
		res = min(bsum, res);
		for(int i = n;i;--i)
		{
			if(sufsum[i + 1] > res) break;
			res = min(res,max(A[i].a,(int)sufsum[i + 1]));
			//printf("%d %d\n",i,p);
		}
		printf("%d\n",res);
	}
	return 0;
}
