#include <cstdio>
const int maxn = 1e5 + 100;
#define int long long
int l, k, x[maxn];

int check(long long num)
{
    int passed = 0;
    long long now = 0;
    for (int i = 1; i <= l; ++i)
    {
        now += x[i];
        if (now < 0) now = 0;
        if (now >= num) now = 0, ++passed;
    }
    return passed;
}
signed main()
{
    scanf("%lld%lld", &l, &k);
    for (int i = 1; i <= l; ++i) scanf("%lld", x + i);
    long long l = 1, r = 1e15, mid, ans = -1;
    while (l <= r)
    {
        mid = (l + r) / 2;
        long long now_ans = check(mid);
        if (now_ans >= k)
        {
            l = mid + 1;
            if(now_ans == k) ans = mid;
        }
        else
            r = mid - 1;
    }
    if (ans == -1)
    {
        puts("-1");
        return 0;
    }
    l = 1, r = ans;
    long long ans2 = -1;
    while (l <= r)
    {
        mid = (l + r) / 2;
        long long now_ans = check(mid);
        if(now_ans == k)
            r = mid - 1, ans2 = mid;
        else
            l = mid + 1;
    }
    printf("%lld %lld\n", ans2, ans);
    return 0;
}