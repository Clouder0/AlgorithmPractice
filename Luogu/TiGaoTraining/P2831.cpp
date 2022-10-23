#include <cstdio>
#include <algorithm>
#include <ctype.h>
const int maxn = 20;
int T, n, m, can[maxn][maxn];
double X[maxn], Y[maxn];
const double eps = 1e-10;
template<typename T>
inline T myabs(T x){return x > 0 ? x : -x;}
int f[1 << 18], lg[1 << 18];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d", &n, &m);
        for (int i = 1; i <= n; ++i) scanf("%lf %lf", X + i, Y + i);
        for (int i = 1; i <= n; ++i)
            for (int j = i + 1; j <= n; ++j)
            {
                can[i][j] = 0;
                double a = (Y[i] / X[i] - Y[j] / X[j]) / (X[i] - X[j]);
                double b = (Y[i] / X[i]) - a * X[i];
                if(a > -eps) continue;
                for (int k = 1; k <= n; ++k)
                    if (myabs(a * X[k] * X[k] + b * X[k] - Y[k]) < eps) can[i][j] |= (1 << (k - 1));
                can[j][i] = can[i][j];
            }
        for (int i = 1; i < (1 << n); ++i) f[i] = 1 << 30;
        f[0] = 0;
        lg[1] = 0;
        for (int i = 2; i < (1 << n); ++i) lg[i] = lg[i >> 1] + 1;
        for (int i = 0; i < (1 << n); ++i)
        {
            int j = lg[(i & (-i))] + 1;
            f[i] = std::min(f[i], f[i ^ (1 << (j - 1))] + 1);
            for (int k = j + 1; k <= n; ++k)
                if (i & (1 << (k - 1)))
                {
                    int old = i & ~can[j][k];
                    f[i] = std::min(f[i], f[old] + 1);
                }
        }
        printf("%d\n",f[(1 << n) - 1]);
    }
    return 0;
}