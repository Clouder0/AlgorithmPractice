#include <cstdio>
#include <ctime>
#include <random>
using namespace std;
mt19937 rnd(time(0));
inline int _abs(const int &x){return x>0?x:-x;}
inline int rd(int l,int r)
{
	return (_abs(rnd()) % (r-l+1)) + l;
}
int main()
{
    freopen("","w",stdout);
    return 0;
}
