#include <cstdio>
#include <set>
#include <algorithm>
const int maxn = 1e5 + 100;
int n, k;
int a[maxn], H[maxn], cnt;
int b[maxn];
void add(int x){for(;x<=cnt;x += x & -x) b[x]++;}
int ask(int x) {
    int res = 0;
    for(;x>0;x-= x& -x) res += b[x];
    return res;
}
int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i), a[i] -= k;
    for (int i = 2; i <= n; ++i) a[i] += a[i - 1];
    H[++cnt] = 0;
    for (int i = 1; i <= n; ++i) H[++cnt] = a[i];
    std::sort(H + 1, H + cnt + 1), cnt = std::unique(H + 1, H + cnt + 1) - H - 1;
    for (int i = 1; i <= n; ++i) a[i] = std::lower_bound(H + 1, H + 1 + cnt, a[i]) - H;
    add(std::lower_bound(H + 1, H + cnt + 1, 0) - H);
    long long res = 0;
    for (int i = 1; i <= n; ++i)
    {
        res += ask(a[i]);
        add(a[i]);
    }
    printf("%lld\n", res);
    return 0;
}