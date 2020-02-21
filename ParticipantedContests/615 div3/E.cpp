#include <cstdio>
#include <vector>
using namespace std;
inline int read()
{
    static char c;
    int r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar());
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar());
    return r;
}
const int maxn = 2e5 + 100;
int n, m;
vector<int> a[maxn];
int s[maxn];
int ans;
int main()
{
    n = read();
    m = read();
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            a[i].push_back(read());
    int maxx = n * m;
    for (int j = 0; j < m; ++j)
    {
        for (int i = 0; i < n; ++i)
            s[i] = 0;
        for (int i = 0; i < n; ++i)
        {
            if (a[i][j] > maxx || a[i][j] < j || ((a[i][j] - j - 1) % m) != 0)
                continue;
            int p = (a[i][j] - j - 1) / m;
            if (i >= p)
                s[i - p]++;
            else
                s[i + n - p]++;
        }
        int res = 1 << 30;
        for (int i = 0; i < n; ++i)
            if (n - s[i] + i < res)
                res = n - s[i] + i;
        ans += res;
    }
    printf("%d\n", ans);
    return 0;
}