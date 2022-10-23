#include <algorithm>
#include <cstdio>
#define int long long
const int maxn = 1e5 + 10;
struct node
{
    int h, num, c;
} T[maxn];
bool cmp(const node& a, const node& b) { return a.h < b.h; }
long long n, num[210], csum[maxn], nsum[maxn], treenum;
signed main()
{
    while (~scanf("%lld", &n))
    {
        for (int i = 1; i <= n; ++i) scanf("%lld%lld%lld", &T[i].h, &T[i].c, &T[i].num);
        std::sort(T + 1, T + 1 + n, cmp);
        for (int i = 1; i <= n; ++i) csum[i] = csum[i - 1] + T[i].c * T[i].num, nsum[i] = nsum[i - 1] + T[i].num;
        for (int i = 1; i <= 200; ++i) num[i] = 0;
        long long minn = 1e18;
        for (int l = 1, r; l <= n; l = r + 1)
        {
            long long now = T[l].num;
            r = l;
            while (r < n && T[r + 1].h == T[r].h) ++r, now += T[r].num;
            long long res = csum[n] - csum[r];
            long long need = nsum[n] - 2 * now + 1 - (nsum[n] - nsum[r]);
            if (need <= 0) goto end;
            for (int j = 1; j <= 200; ++j)
            {
                if (need <= num[j])
                {
                    res += need * j;
                    goto end;
                }
                res += j * num[j], need -= num[j];
            }

        end:
            for (int i = l; i <= r; ++i) num[T[i].c] += T[i].num;
            minn = std::min(minn, res);
        }
        printf("%lld\n", minn);
    }
    return 0;
}