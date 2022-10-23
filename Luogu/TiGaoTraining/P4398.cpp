#include <algorithm>
#include <cstdio>
using namespace std;
const int maxn = 51;
int n, A[maxn][maxn], B[maxn][maxn], f[maxn][maxn][maxn][maxn], ans;
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) scanf("%d", A[i] + j);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) scanf("%d", B[i] + j);
    for (int a = 1; a <= n; ++a)
        for (int b = 1; b <= n; ++b)
            for (int c = 1; c <= n; ++c)
                for (int d = 1; d <= n; ++d)
                    if(A[a][b] == B[c][d])
                    {
                        f[a][b][c][d] = min(f[a - 1][b][c - 1][d], min(f[a][b - 1][c][d - 1], f[a - 1][b - 1][c - 1][d - 1])) + (A[a][b] == B[c][d]);
                        //                    printf("f[%d][%d][%d][%d]=%d\n",a,b,c,d,f[a][b][c][d]);
                        ans = max(ans, f[a][b][c][d]);
                    }
    printf("%d\n", ans);
    return 0;
}