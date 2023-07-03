#include <cstdio>
#include <list>
#include <algorithm>
#include <set>

using namespace std;

const int maxn = 1e3 + 10;
int n, m, a[maxn][maxn];
set<int> S;
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) scanf("%d", a[i] + j);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (S.find(a[i][j]) != S.end()) {
                puts("NO");
                return 0;
            }
            else S.insert(a[i][j]);
    puts("YES");
    return 0;
}