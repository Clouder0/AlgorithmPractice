#include <cstdio>
const int maxn = 1e4 + 100;
int T, n, a[maxn], ans1[maxn * 3], ans2[maxn * 3], ans3[maxn * 3], cnt;
int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        cnt = 0;
        int sum = 0;
        for (int i = 1; i <= n; ++i) scanf("%d", a + i), sum += a[i];
        if (sum % n) { puts("-1"); continue; }
        sum /= n;
        for (int i = 2; i <= n; ++i)
        {
            int need = (i - (a[i] % i)) % i;
            if (need) ans1[++cnt] = 1, ans2[cnt] = i, ans3[cnt] = need;
            ans1[++cnt] = i, ans2[cnt] = 1, ans3[cnt] = (a[i] + need) / i;
        }
        for (int i = 2; i <= n; ++i) ans1[++cnt] = 1, ans2[cnt] = i, ans3[cnt] = sum;
        printf("%d\n", cnt);
        for (int i = 1; i <= cnt; ++i) printf("%d %d %d\n", ans1[i], ans2[i], ans3[i]);
    }
    return 0;
}