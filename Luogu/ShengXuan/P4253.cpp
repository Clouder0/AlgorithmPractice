#include <cstdio>
#include <algorithm>
#include <cctype>
using namespace std;
const int bufSize = 1e6;
inline char nc()
{
	#ifdef DEBUG
	return getchar();
	#endif
	static char buf[bufSize], *p1 = buf, *p2 = buf;
	return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
template<typename T>
inline T read(T &r)
{
	static char c;
	static int flag;
	flag = 1, r = 0;
	for (c = nc(); !isdigit(c); c = nc()) if (c == '-') flag = -1;
	for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
	return r *= flag;
}
const int maxn = 2e5 + 100;
#define ll long long
int n, a[maxn], b[maxn], lg[maxn];
ll f[maxn][19][2], dis[maxn][19];
int main()
{
	read(n);
    for (int i = 2; i <= n; ++i) lg[i] = lg[i >> 1] + 1;
    for (int i = 1; i <= n; ++i) read(a[i]);
    for (int i = 2; i <= n; ++i) read(b[i]);
    for (int i = 2; i <= n; ++i) for (int j = 1; j <= lg[i]; ++j) dis[i][j] = dis[i >> 1][j - 1] + b[i];
    for (int i = n; i; --i)
    {
        for (int j = 1; j <= lg[i] + 1; ++j)
        {
            int p = (i >> (j - 1)) ^ 1;
            if ((i << 1) > n)
            {
                //leaf
                f[i][j][0] = dis[i][j] * a[i >> j];
                f[i][j][1] = (dis[i][j] + dis[p][1]) * a[p];
            }
			else if((i << 1 | 1) > n)
			{
				//only left
				int ls = i << 1;
                f[i][j][0] = f[ls][j + 1][0] + dis[ls][1] * a[ls];
                f[i][j][1] = f[ls][j + 1][1] + dis[ls][1] * a[ls];
            }
			else
			{
				//both
                int ls = i << 1, rs = i << 1 | 1;
                f[i][j][0] = min(f[ls][j + 1][0] + f[rs][1][1] + dis[rs][1] * a[rs], f[rs][j + 1][0] + f[ls][1][1] + dis[ls][1] * a[ls]);
                f[i][j][1] = min(f[ls][j + 1][1] + f[rs][1][1] + dis[rs][1] * a[rs], f[rs][j + 1][1] + f[ls][1][1] + dis[ls][1] * a[ls]);
            }
        }
    }
	long long res = 1ll << 62;
    for (int s = 1; s <= n; ++s)
    {
        long long t = f[s][1][0];
        for (int now = s >> 1, last = s; now > 0; now >>= 1, last >>= 1)
        {
            int bro = last ^ 1;
            if (bro <= n) t += dis[bro][1] * a[bro] + f[bro][2][0];
            else t += dis[now][1] * a[now >> 1];
        }
        res = std::min(res, t);
    }
    printf("%lld\n",res);
    return 0;
}