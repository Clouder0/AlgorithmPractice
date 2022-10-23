#include <cstdio>
#include <cstring>
using namespace std;
template <typename T> inline T _max(const T& a, const T& b) { return a > b ? a : b; }
template <typename T> inline T _min(const T& a, const T& b) { return a < b ? a : b; }
template <typename T>
inline void read(T& r)
{
    static char c;r=0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar()) ;
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar()) ;
}
const int maxn = 1e5 + 10;
int n, m, a[maxn], f[maxn];
long long sum[maxn];
int main()
{
	//freopen("book.in","r",stdin);
	//freopen("std.out","w",stdout);
    read(n), read(m);
    for (int i = 1; i <= n; ++i) read(a[i]), sum[i] = sum[i - 1] + a[i];
    memset(f, 0x3f, sizeof(f));
    f[0] = 0;
    for (int i = 1; i <= n; ++i)
    {
        int maxx = -1;
        for (int j = i; j; --j)
        {
            if (sum[i] - sum[j - 1] > m) break;
            maxx = _max(maxx, a[j]), f[i] = _min(f[i], f[j - 1] + maxx);
        }
    }
    printf("%d",f[n]);
    return 0;
}
