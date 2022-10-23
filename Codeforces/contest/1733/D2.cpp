#include <cstdio>
#include <cstring>
#include <algorithm>
#define int long long
const int maxn = 5010;
const int inf =  1ll << 60;
int T, n, x, y;
int a[maxn], f[maxn][maxn][2];
char s1[maxn], s2[maxn];
inline bool has_not_end_one(int a, int b, int c)
{
    if(b > a || b < 0) return false;
    return b - c > 0;
}
inline bool has_not_end_zero(int a, int b, int c)
{
    if(b > a || b < 0) return false;
    return a - b - (c == 0) > 0;
}
inline bool has_end_one(int a, int b, int c)
{
    if(b > a || b < 0) return false;
    return b && c;
}
inline bool has_end_zero(int a, int b, int c)
{
    if(b > a || b < 0) return false;
    return c == 0 && a - b > 0;
}
signed main()
{
    scanf("%lld",&T);
    int num = 0;
    while (T--)
    {
        ++num;
        scanf("%lld%lld%lld", &n, &x, &y);
        if (n != 2 && y * 2 < x) x = 2 * y;
        scanf("%s", s1 + 1), scanf("%s", s2 + 1);
        for (int i = 1; i <= n; ++i) a[i] = (s1[i] != s2[i]);
        for (int i = 0; i <= n + 1; ++i)
            for (int j = 0; j <= n + 1; ++j) f[i][j][0] = f[i][j][1] = inf;
        if (a[1])
            f[1][1][1] = 0;
        else
            f[1][0][0] = 0;
        for (int i = 2; i <= n; ++i)
        {
            if(a[i])
            {
                for (int j = 0; j <= i; ++j)
                {
                    // execute not end 1
                    if (has_not_end_one(i - 1, j + 1, 0))
                        f[i][j][0] = std::min(f[i][j][0], f[i - 1][j + 1][0] + y);
                    if (has_not_end_one(i - 1, j + 1, 1))
                        f[i][j][0] = std::min(f[i][j][0], f[i - 1][j + 1][1] + y);
                    // execute not end 0
                    if (has_not_end_zero(i - 1, j - 1, 0))
                        f[i][j][0] = std::min(f[i][j][0], f[i - 1][j - 1][0] + y);
                    if (has_not_end_zero(i - 1, j - 1, 1))
                        f[i][j][0] = std::min(f[i][j][0], f[i - 1][j - 1][1] + y);
                    // execute end 1
                    if (has_end_one(i - 1, j + 1, 1))
                        f[i][j][0] = std::min(f[i][j][0], f[i - 1][j + 1][1] + x);
                    // execute end 0
                    if (has_end_zero(i - 1, j - 1, 0))
                        f[i][j][0] = std::min(f[i][j][0], f[i - 1][j - 1][0] + x);
                    // no execute
                    if (j - 1 >= 0)
                        f[i][j][1] = std::min(f[i][j][1], std::min(f[i - 1][j - 1][0], f[i - 1][j - 1][1]));
                }
            }
            else
            {
                for (int j = 0; j <= i; ++j)
                {
                    // execute not end 1
                    if (has_not_end_one(i - 1, j, 0))
                        f[i][j][1] = std::min(f[i][j][1], f[i - 1][j][0] + y);
                    if (has_not_end_one(i - 1, j, 1))
                        f[i][j][1] = std::min(f[i][j][1], f[i - 1][j][1] + y);
                    // execute not end 0
                    if (has_not_end_zero(i - 1, j - 2, 0))
                        f[i][j][1] = std::min(f[i][j][1], f[i - 1][j - 2][0] + y);
                    if (has_not_end_zero(i - 1, j - 2, 1))
                        f[i][j][1] = std::min(f[i][j][1], f[i - 1][j - 2][1] + y);
                    // execute end 1
                    if (has_end_one(i - 1, j, 1))
                        f[i][j][1] = std::min(f[i][j][1], f[i - 1][j][1] + x);
                    // execute end 0
                    if (has_end_zero(i - 1, j - 2, 0))
                        f[i][j][1] = std::min(f[i][j][1], f[i - 1][j - 2][0] + x);
                    // no execute
                    f[i][j][0] = std::min(f[i][j][0], std::min(f[i - 1][j][0], f[i - 1][j][1]));
                }
            }
        }
//        if(T > 10)
//        {
//            if (num == 184)
//            {
//                printf("%lld %lld %lld\n", n, x, y);
//                for (int i = 1; i <= n; ++i) printf("%lld",a[i]);
//                puts("");
//                return 0;
//            }
//        }
//        else
//        {
            if (f[n][0][0] >= inf)
                puts("-1");
            else
                printf("%lld\n", f[n][0][0]);
//        }
    }
    return 0;
}