#include <cstdio>
#include <sstream>
#include <ctime>
#include <random>
#include <string>
using namespace std;
mt19937 rnd(time(0));
inline int _abs(const int &x){return x>0?x:-x;}
inline int rd(int l,int r)
{
	return (_abs(rnd()) % (r-l+1)) + l;
}
int l = 15;
int r = 20;
int main()
{
	string a = "partition",b = ".in",c;
	stringstream ss;
	for(;l<=r;++l)
	{
		ss.clear();
		ss << l;
		ss >> c;
		freopen((a + c + b).c_str(),"w",stdout);
		int n = rd(6,200000);
    	int k = rd(2,600);
    	printf("%d %d",n,k);
    	fclose(stdout);
	}
    return 0;
}
