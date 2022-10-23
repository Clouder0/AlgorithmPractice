#include <cstdio>
#include <algorithm>
using namespace std;
inline bool isprime(const int &x)
{
	for(int i = 2;i*i<=x;++i)
		if(!(x%i))	return false;
	return true;
}
int a,b;
int primes[100000];
int cnt;
int main()
{
	scanf("%d%d",&a,&b);
	
	int temp;
	
	//One
	for(int d1 = 1;d1<=9;++d1)
	{
		temp = d1;
		if(temp >= a && temp <= b && isprime(temp))	primes[++cnt] = temp;
		temp = d1 * 10 + d1;
		if(temp >= a && temp <= b && isprime(temp))	primes[++cnt] = temp;
	}
	
	//Two and Three
	for(int d1 = 1;d1<=9;d1+=2) 
		for(int d2 = 0;d2<=9;++d2)
		{
			temp = d1*100 + d2*10 + d1;
			if(temp >= a && temp <= b && isprime(temp))	primes[++cnt] = temp;
			temp = d1*1000 + d2*100 + d2 * 10 + d1;
			if(temp >= a && temp <= b && isprime(temp))	primes[++cnt] = temp;
		}
		
	for(int d1 = 1;d1<=9;d1+=2) 
		for(int d2 = 0;d2<=9;++d2)
			for(int d3 = 0;d3<=9;++d3)
			{
				temp = d1*10000 + d2*1000 + d3 * 100 + d2 * 10 + d1;
				if(temp >= a && temp <= b && isprime(temp))	primes[++cnt] = temp;
				temp = d1*100000 + d2*10000 + d3 * 1000 + d3 * 100 + d2 * 10 + d1;
				if(temp >= a && temp <= b && isprime(temp))	primes[++cnt] = temp;
			}
	
	for(int d1 = 1;d1<=9;d1+=2) 
		for(int d2 = 0;d2<=9;++d2)
			for(int d3 = 0;d3<=9;++d3)
				for(int d4 = 0;d4<=9;++d4)
				{
					temp = d1*1000000 + d2*100000 + d3 * 10000 + d4 * 1000 + d3 * 100 + d2 * 10 + d1;
					if(temp >= a && temp <= b && isprime(temp))	primes[++cnt] = temp;
					temp = d1*10000000 + d2*1000000 + d3 * 100000 + d4 * 10000 + d4 * 1000 + d3 * 100 + d2 * 10 + d1;
					if(temp >= a && temp <= b && isprime(temp))	primes[++cnt] = temp;
				}
	sort(primes+1,primes+1+cnt);
	for(int i = 1;i<=cnt;++i)
		printf("%d\n",primes[i]);
	return 0;
}
