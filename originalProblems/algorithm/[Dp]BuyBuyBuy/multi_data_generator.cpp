#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#include <cstdio>
#include <sstream>
#include <ctime>
#include <random>
#include <string>
using namespace std;
mt19937 rnd(time(0));
inline int _abs(const int &x) { return x > 0 ? x : -x; }
inline int rd(int l, int r)
{
	return (_abs(rnd()) % (r - l + 1)) + l;
}
int l = 1;
int r = 10;
string title = "BuyBuyBuy";
string surfix = ".in";
string id;
void generate()
{
	int T = rd(1,100);
	printf("%d\n",T);
	while(T--)
	{
		int n = rd(1,100000);
		printf("%d\n",n);
		for(int i = 1;i<=n;++i)
		{
			int temp = rd(0,10000);
			if(rd(0,1))
				temp *= -1;
			printf("%d ",temp);
		}
		putchar('\n');
	}
}
int main()
{
	stringstream ss;
	for (; l <= r; ++l)
	{
		ss.clear();
		ss << l;
		ss >> id;
		freopen((title + id + surfix).c_str(), "w", stdout);
		generate();
		fclose(stdout);
	}
	return 0;
}
