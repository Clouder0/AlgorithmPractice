#include <cstdio>
using namespace std;
int n;
bool notprime[210000];
int primes[50000];
int cnt;
void init()
{
	notprime[1] = notprime[0] = 1;
	for(int i = 2;i<=n;++i)
	{
		if(!notprime[i])	primes[++cnt] = i;
		for(int j = 1;j<=cnt && primes[j] * i <= n;++j)
		{
			notprime[primes[j] * i] = true;
			if(i % primes[j] == 0)	break;
		}
	}
}
int main()
{
	scanf("%d",&n);
	init();
	int k;
	for(int i = 1;i<=cnt;++i)
		for(int j = i;j<=cnt;++j)
		{
			k = n - primes[i] - primes[j];
			if(k <= 0)	continue;
			if(!notprime[k])
			{
				printf("%d %d %d",primes[i],primes[j],k);
				return 0;
			}
		}
	return 0;
}
