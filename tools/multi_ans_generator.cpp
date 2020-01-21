#include <cstdio>
#include <sstream>
#include <string>
#include <cstring>
using namespace std;
void init()
{
}
void solve()
{
}
int l = 1;
int r = 10;
string title = "partition";
string surfix1 = ".in";
string surfix2 = ".out";
string id;
int main()
{
	stringstream ss;
	for (; l <= r; ++l)
	{
		ss.clear();
		ss << l;
		ss >> id;
		freopen((title + id + surfix1).c_str(), "r", stdin);
		freopen((title + id + surfix2).c_str(), "w", stdout);
		init();
		solve();
		fclose(stdin);
		fclose(stdout);
	}
	return 0;
}
