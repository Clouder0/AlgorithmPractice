#include <cstdio>
const int maxn = 1e5 + 100;
int n;
double f[maxn],g[maxn];
int main()
{
    scanf("%d",&n);
    for(int i = n - 1;i>=0;--i)
    {
        f[i] = f[i + 1] + 1.0 * n / (1.0 * n - i);
        g[i] = (1.0 * i) / (n - i) * f[i] + g[i + 1] + f[i + 1] + (1.0 * n) / (n - i);
    }
    printf("%.2f",g[0]);
    return 0;
}