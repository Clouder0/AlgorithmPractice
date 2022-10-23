#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 5100;
#define int long long
struct node
{
	int t,x;
}A[maxn];
inline bool cmp(const node &a,const node &b){return a.t < b.t;}
int n,f[maxn][maxn],minn[maxn];
inline int dis(int a,int b){return abs(A[a].x - A[b].x);}
signed main()
{
	scanf("%lld",&n);
	for(int i = 1;i<=n;++i) scanf("%lld %lld",&A[i].t,&A[i].x);
	sort(A + 1,A + 1 + n,cmp);
	for(int i = 1;i<=n;++i) minn[i] = 1 << 30;
	f[0][0] = 1;
	for(int i = 0;i<n;++i)
	{
		if(minn[i] <= A[i].t)
		{
			minn[i + 1] = min(minn[i + 1],max(A[i].t,minn[i] + dis(i,i+1)));
			for(int j = i + 2;j<=n;++j)//place a clone
				if(max(A[i].t, minn[i] + dis(i,j)) + dis(j,i+1) <= A[i+1].t) f[i+1][j] = 1;
		}
		if(i < n - 1 && f[i][i+1]) //go directly to i + 2 and leave the i + 1 to clone onw
		{
			minn[i+2] = min(minn[i+2],max(A[i+1].t,A[i].t + dis(i,i + 2)));
			for(int j = i + 3;j<=n;++j) if(max(A[i+1].t,A[i].t + dis(i,j)) + dis(j,i + 2) <= A[i+2].t)
				f[i+2][j] = 1;		
		}
		if(A[i].t + dis(i,i+1) <= A[i+1].t) for(int j = i + 2;j<=n;++j) f[i+1][j] |= f[i][j];
	}
	if(minn[n] <= A[n].t || f[n-1][n]) puts("YES"); else puts("NO");
	return 0;
} 
