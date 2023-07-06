#include <cstdio>


const int maxn = 60;
int n;
long long a[maxn];
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%lld", a + i);
    long long ans = 0;
    while (1)
    {
        bool flag = 1;
        for (int i = 1; flag && i <= n; ++i) flag &= (a[i] < n);
        if (flag) break;
        long long add_times = 0;
        for (int i = 1; i <= n; ++i)
            if ((a[i] + add_times) >= n)
            {
                long long times = (a[i] + add_times) / n;
                ans += times;
                a[i] = a[i] - (n + 1) * times;
                add_times += times;
            }
        for (int i = 1; i <= n; ++i) a[i] = a[i] + add_times;
    }
    printf("%lld\n",ans);
    return 0;
}