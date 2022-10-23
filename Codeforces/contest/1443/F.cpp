#include <cstdio>
const int maxn = 2e5 + 100;
const int mod = 998244353;
int T, n, k, a[maxn], b[maxn], c[maxn], pos[maxn];
int main()
{
    scanf("%d",&T);
    while (T--)
    {
        scanf("%d %d",&n,&k);
        for (int i = 1; i <= n; ++i) scanf("%d", a + i), pos[a[i]] = i, c[i] = 0;
        for (int i = 1; i <= k; ++i) scanf("%d", b + i), b[i] = pos[b[i]];
        for (int i = 1; i <= k; ++i) c[b[i]] = i;
        int res = 1;
        for (int i = 1; i <= k; ++i)
        {
            int t = 0;
            t += (b[i] > 1 && c[b[i] - 1] < i);
            t += (b[i] < n && c[b[i] + 1] < i);
            if (!t) goto fail;
            else if (t == 2) res = (res << 1) % mod;
        }
        printf("%d\n", res);
        continue;
    fail:
        puts("0");
    }
    return 0;
}
