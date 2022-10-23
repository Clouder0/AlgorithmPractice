#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
long long n;
int main()
{
	scanf("%lld",&n);
	long long t = sqrt(2 * (n + 1));
	while(t * (t + 1) / 2 <= (n + 1)) ++t;
	--t;
	printf("%lld\n",n - t + 1);
	return 0;
}
