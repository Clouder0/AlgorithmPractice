#include <cstdio>
#include <set>
using namespace std;
const int maxn = 2e5 + 100;
set<int> S;
int n, m, A[maxn], B[maxn];
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%d", A + i);
    for (int i = 1; i <= m; ++i) scanf("%d", B + i), S.insert(B[i]);
    for (int i = 1; i <= n; ++i)
        if (S.count(A[i])) printf("%d ", A[i]);
    return 0;
}