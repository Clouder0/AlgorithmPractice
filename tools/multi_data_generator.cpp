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
string title = "partition";
string surfix = ".in";
string id;
void generate()
{
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
