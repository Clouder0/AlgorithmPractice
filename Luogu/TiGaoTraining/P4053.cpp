#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
const int maxn = 3e5 + 100;
int n;
struct node
{
	int t1,t2;
}A[maxn];
bool cmp(const node &a,const node &b){return a.t2 < b.t2;}
priority_queue<int> q;
int main()
{
	scanf("%d",&n);
	for(int i = 1;i<=n;++i) scanf("%d %d",&A[i].t1,&A[i].t2);
	std::sort(A + 1,A + 1 + n,cmp);
	int now = 0,res = 0;
	for(int i = 1;i<=n;++i)
	{
		if(now + A[i].t1 <= A[i].t2) now += A[i].t1,q.push(A[i].t1),++res;
		else if(q.size() && A[i].t1 <= q.top()) now = now - q.top() + A[i].t1,q.pop(),q.push(A[i].t1);
	}
	printf("%d\n",res);
	return 0;
}
