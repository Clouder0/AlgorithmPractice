#include <algorithm>
#include <cstdio>

#define int long long
const int maxn = 1e5 + 100;

int T, n;
struct node
{
    int x, t;
} A[maxn];
inline bool cmp(const node& a, const node& b)
{
    if (a.x == b.x) return a.t < b.t;
    return a.x < b.x;
}
int lmax[maxn], rmax[maxn];
signed main()
{
    scanf("%lld", &T);
    while (T--)
    {
        scanf("%lld", &n);
        for (int i = 1; i <= n; ++i) scanf("%lld", &A[i].x);
        for (int i = 1; i <= n; ++i) scanf("%lld", &A[i].t);
        if (n == 1)
        {
            printf("%lld\n", A[1].x);
            continue;
        }
        std::sort(A + 1, A + n + 1, cmp);
        lmax[1] = A[1].t;
        for (int i = 2; i <= n; ++i) lmax[i] = std::max(lmax[i - 1] + A[i].x - A[i - 1].x, A[i].t);
        rmax[n] = A[n].t;
        for (int i = n - 1; i; --i) rmax[i] = std::max(rmax[i + 1] + A[i + 1].x - A[i].x, A[i].t);
        double ans_t = 1e30, ans_pos = -1;
        for (int i = 1; i < n; ++i)
        {
            // i, i + 1
            int l = lmax[i], r = rmax[i + 1];
            int d = A[i + 1].x - A[i].x;
            // printf("l=%d,r=%d,d=%d\n",l,r,d);
            if (A[i + 1].x - A[i].x >= std::abs(r - l))
            {
                double total_t = 1.0 * (l + r + A[i + 1].x - A[i].x) / 2;
                double pos = total_t - l + A[i].x;
                if (total_t < ans_t)
                {
                    ans_pos = pos;
                    ans_t = total_t;
                }
                continue;
            }
            if (std::max(lmax[i], rmax[i]) < ans_t)
            {
                ans_t = std::max(lmax[i], rmax[i]);
                ans_pos = A[i].x;
            }
            // printf("i=%d, ans_pos=%.2f\n", i, ans_pos);
        }
        if (std::max(lmax[n], rmax[n]) < ans_t)
        {
            ans_t = std::max(lmax[n], rmax[n]);
            ans_pos = A[n].x;
        }

        printf("%.6f\n", ans_pos);
    }
    return 0;
}