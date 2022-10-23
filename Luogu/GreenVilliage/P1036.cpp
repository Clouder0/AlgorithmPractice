#include <cstdio>
using namespace std;
inline bool isprime(const int &x)
{
	for(int i = 2;i*i<=x;++i)
		if(!(x % i))	return false;
	return true;
}
int ans,temp,n,k;
int all[22];
void dfs(int nown,int nowk)
{
	if(n - nown < k - nowk)	return;
	if(nowk == k)
	{
		ans += isprime(temp);
		return;
	}
	for(int i = nown + 1;i <= n;++i)
	{
		temp += all[i];
		dfs(i,nowk+1);
		temp -= all[i];
	}
}
int main()
{
	scanf("%d%d",&n,&k);
	for(int i = 1;i<=n;++i)
		scanf("%d",all+i);
	dfs(0,0);
	printf("%d",ans);
	return 0;
}
