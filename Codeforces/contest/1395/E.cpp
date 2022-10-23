#include <algorithm>
#include <cstdio>
#include <ctime>
#include <ctype.h>
#include <vector>

using namespace std;
const int bufSize = 1e6;
#define DEBUG
inline char nc()
{
#ifdef DEBUG
    return getchar();
#endif
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
template <typename T>
inline T read(T& r)
{
    static char c;
    static int flag;
    flag = 1, r = 0;
    for (c = nc(); !isdigit(c); c = nc()) if (c == '-') flag = -1;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r *= flag;
}
const int maxn = 2e5 + 100;
int n, m, k;
int sum;
int a[maxn];
int U[maxn], V[maxn];
vector<int> E[maxn];
int val[10][10];
int c[10], ans;
void dfs(int x)
{
    if (x == k + 1)
    {
        int tsum = 0;
        for (int i = 1; i <= k; ++i) tsum += val[i][c[i]];
        if (sum == tsum) ++ans;
        return;
    }
    for (int i = 1; i <= x; ++i) c[x] = i, dfs(x + 1);
}
int main()
{
    srand(time(0));
    read(n), read(m), read(k);
    for (int i = 1; i <= n; ++i) sum += (a[i] = rand());
    for (int i = 1; i <= m; ++i)
    {
        int a, b, c;
        read(a), read(b), read(c);
        U[c] = a, V[c] = b;
    }
    for (int i = 1; i <= m; ++i) E[U[i]].push_back(V[i]);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= (int)E[i].size(); ++j)
            val[E[i].size()][j] += a[E[i][j - 1]];
    dfs(1);
    printf("%d\n", ans);
    return 0;
}