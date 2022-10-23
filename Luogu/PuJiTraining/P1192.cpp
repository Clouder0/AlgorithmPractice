#include <cstdio>
using namespace std;
int f[100010];
int n, k;
const int mod = 100003;
int main()
{
    scanf("%d%d", &n, &k);
    f[0] = f[1] = 1;
    for (int i = 2; i <= k; ++i)
        f[i] = (f[i - 1] << 1) % mod;
    for (int i = k + 1; i <= n; ++i)
        f[i] = ((f[i - 1] << 1) - f[i - k - 1] + mod) % mod;
    printf("%d", f[n]);
    return 0;
}