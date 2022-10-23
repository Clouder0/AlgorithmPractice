#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
int n, x1, x2, x3;
int f[2][1100][1100];
int a[7], b[7], c[7], num[7];
int d[7] = {0, 100, 50, 20, 10, 5, 1};
int main()
{
    scanf("%d %d %d",&x1,&x2,&x3);
    int summoney = 0, af = 0, bf = 0, cf = 0;
    for (int i = 1; i <= 6; ++i) scanf("%d", a + i), num[i] += a[i], summoney += d[i] * a[i], af += d[i] * a[i];
    for (int i = 1; i <= 6; ++i) scanf("%d", b + i), num[i] += b[i], summoney += d[i] * b[i], bf += d[i] * b[i];
    for (int i = 1; i <= 6; ++i) scanf("%d", c + i), num[i] += c[i], summoney += d[i] * c[i], cf += d[i] * c[i];
    int now = 0, last = 1;
    memset(f, 0x3f, sizeof(f));
    f[last][af][bf] = 0;
    af -= x1, bf += x1, bf -= x2, cf += x2, cf -= x3, af += x3;
    int ans = 1<<30;
    for (int i = 1; i <= 6; ++i)
    {
        for (int j = 0; j <= summoney; ++j)
            for (int k = 0; j + k <= summoney; ++k)
            {
                f[now][j][k] = min(f[now][j][k], f[last][j][k]);
                if (f[last][j][k] > 100000) continue;
                int z = summoney - j - k;
                for (int ah = 0; ah <= num[i]; ++ah)
                    for (int bh = 0; ah + bh <= num[i]; ++bh)
                    {
                        int ch = num[i] - ah - bh;
                        int anow = j - (a[i] - ah) * d[i];
                        int bnow = k - (b[i] - bh) * d[i];
                        int cnow = z - (c[i] - ch) * d[i];
                        int w = (abs(a[i] - ah) + abs(b[i] - bh) + abs(c[i] - ch)) / 2;
                        if (anow < 0 || bnow < 0 || cnow < 0 || anow + bnow + cnow > summoney) continue;
                        f[now][anow][bnow] = min(f[now][anow][bnow], f[last][j][k] + w);
                    }
            }
        ans = min(ans, f[now][af][bf]);
        now ^= 1, last ^= 1;
    }
    if (ans < 100000) printf("%d\n", ans);
    else puts("impossible");
    return 0;
}