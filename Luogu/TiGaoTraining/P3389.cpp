#include <algorithm>
#include <cmath>
#include <cstdio>
const int maxn = 110;
int n;
double a[maxn][maxn];
const double eps = 1e-8;
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= n + 1; ++j) scanf("%lf", &a[i][j]);
    for (int i = 1; i <= n; ++i) // 选择列
    {
        //寻找系数最大行
        int maxx = i;
        for (int j = i + 1; j <= n; ++j) if (fabs(a[j][i]) > fabs(a[maxx][i])) maxx = j; 
        //将系数最大行交换至第 i 行
        for (int j = 1; j <= n + 1; ++j) std::swap(a[i][j], a[maxx][j]);
        //系数全零
        if (fabs(a[i][i]) < eps) goto fail;
        for (int j = 1; j <= n; ++j)
        {
            if (j == i) continue;
            //消元
            double t = a[j][i] / a[i][i];
            for (int k = i + 1; k <= n + 1; ++k) a[j][k] -= a[i][k] * t;
        }
    }
    //解一元一次方程
    for (int i = 1; i <= n; ++i) printf("%.2f\n", a[i][n + 1] / a[i][i]);
    return 0;
fail:
    puts("No Solution");
    return 0;
}