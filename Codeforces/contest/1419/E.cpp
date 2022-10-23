#include <algorithm>
#include <cstdio>
const int maxn = 2e5 + 100;
#define int long long
int T, n;
int d[maxn], cnt, used[maxn];
int k[maxn], pri[maxn], pcnt;
signed main()
{
    scanf("%lld", &T);
    while (T--)
    {
        scanf("%lld", &n);
        pcnt = cnt = 0;
        for (int i = 2; i * i <= n; ++i)
            if ((n % i) == 0) d[++cnt] = i, d[++cnt] = n / i;
        d[++cnt] = n;
        std::sort(d + 1, d + 1 + cnt), cnt = std::unique(d + 1, d + 1 + cnt) - d - 1;
        for (int i = cnt + 1; i <= cnt + 100; ++i) d[i] = 0;
        for (int i = 1; i <= cnt + 100; ++i) k[i] = pri[i] = used[i] = 0;
        int x = n;
        for (int i = 2; i * i <= n; ++i)
            if ((x % i) == 0)
            {
                pri[++pcnt] = i;
                while ((x % i) == 0) ++k[pcnt], x /= i;
            }
        if (x > 1) pri[++pcnt] = x, k[pcnt] = 1;
        for (int i = 1; i <= cnt + 10; ++i) used[i] = 0;
        if (pcnt == 2)
        {
            if (k[1] == 1 && k[2] == 1)
                printf("%lld %lld %lld\n1\n", pri[1], pri[1] * pri[2], pri[2]);
            else
            {
                if (k[1] == 1) std::swap(pri[1], pri[2]), std::swap(k[1], k[2]);
                printf("%lld ", pri[1]);
                for (int i = 1; i <= cnt; ++i)
                    if (d[i] != pri[1] && d[i] != pri[2] && d[i] != pri[1] * pri[2] && d[i] != pri[1] * pri[1] * pri[2])
                        printf("%lld ", d[i]);
                printf("%lld %lld %lld\n0\n", pri[1] * pri[2], pri[2], pri[1] * pri[1] * pri[2]);
            }
            continue;
        }
        pri[pcnt + 1] = pri[1];
        for (int i = 1; i <= pcnt; ++i)
            for (int j = 1; j <= cnt; ++j)
                if (d[j] == pri[i] || d[j] == pri[i] * pri[i + 1]) used[j] = 1;
        for (int i = 1; i <= pcnt; ++i)
        {
            printf("%lld ", pri[i]);
            for (int j = 1; j <= cnt; ++j)
                if (!used[j] && (d[j] % pri[i]) == 0)
                    printf("%lld ", d[j]), used[j] = 1;
            printf("%lld ", pri[i] * pri[i + 1]);
        }
        printf("\n0\n");
    }
    return 0;
}