#include <cstdio>
#include <sstream>
#include <string>
#include <cstring>
using namespace std;
template <typename T>
inline int read(T &r)
{
	static char c;static int flag;flag = 1, r = 0;
	for (c = getchar(); c > '9' || c < '0'; c = getchar())if (c == '-')flag = -1;
	for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar());
	return r *= flag;
}
const int maxn = 100000;
int n, T;
int all[maxn];
void init()
{
	memset(all, 0, sizeof(all));
}
void solve()
{
	read(T);
	while (T--)
	{
		read(n);
		for (int i = 1; i <= n; ++i)
			read(all[i]);
		int sum = 0;
		for (int i = 1; i < n; ++i)
		{
			sum += all[i];
			if (sum <= 0)
			{
				printf("What a Shame!\n");
				goto end;
			}
		}
		sum = 0;
		for (int i = n; i > 1; --i)
		{
			sum += all[i];
			if (sum <= 0)
			{
				printf("What a Shame!\n");
				goto end;
			}
		}
		printf("Just do it!\n");
		end:;
	}
	return;
}
int l = 1;
int r = 10;
string title = "BuyBuyBuy";
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
