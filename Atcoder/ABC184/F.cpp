#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn = 50;
int n,t,a[maxn],mid;
vector<int> A[maxn],B[maxn];
vector<int> S,T;
int main()
{
	scanf("%d %d",&n,&t);
	for(int i = 1;i<=n;++i) scanf("%d",a + i);
	mid = n >> 1;
	A[0].push_back(0);
	for(int i = 1;i<=mid;++i)
	{
		S.clear(),T.clear();
		for(vector<int>::iterator it = A[i - 1].begin();it!=A[i - 1].end();++it)
			if(*it + a[i] <= t) S.push_back(*it + a[i]);
		vector<int>::iterator p1 = A[i - 1].begin(),p2 = S.begin();
		while(p1 != A[i - 1].end() && p2 != S.end())
			if(*p1 <= *p2) T.push_back(*p1++); else T.push_back(*p2++);
		while(p1 != A[i - 1].end()) T.push_back(*p1++);
		while(p2 != S.end()) T.push_back(*p2++);
		A[i] = T;
	}
	B[mid].push_back(0);
	for(int i = mid + 1;i<=n;++i)
	{
		S.clear(),T.clear();
		for(vector<int>::iterator it = B[i - 1].begin();it!=B[i - 1].end();++it)
			if(*it + a[i] <= t) S.push_back(*it + a[i]);
		vector<int>::iterator p1 = B[i - 1].begin(),p2 = S.begin();
		while(p1 != B[i - 1].end() && p2 != S.end())
			if(*p1 <= *p2) T.push_back(*p1++); else T.push_back(*p2++);
		while(p1 != B[i - 1].end()) T.push_back(*p1++);
		while(p2 != S.end()) T.push_back(*p2++);
		B[i] = T;
	}
	int p = 0,res = 0;
	for(int i = B[n].size() - 1;i >= 0;--i)
	{
		while(p < A[mid].size() && B[n][i] + A[mid][p] <= t) ++p;
		if(p) res = max(res,B[n][i] + A[mid][p-1]);
	}
	printf("%d\n",res);
	return 0;
}
