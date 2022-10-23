#include <cstdio>
#include <algorithm>
const int maxn = 1e5 + 100;
int T, n, a[maxn], b[maxn], acnt, bcnt;
long long aprod[10], bprod[10];
long long reaprod[10], rebprod[10];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        acnt = bcnt = 0;
        long long res = -(1ll << 62);
        for (int i = 1, x; i <= n; ++i)
        {
            scanf("%d", &x);
            if (x >= 0) a[++acnt] = x;
            else b[++bcnt] = -x;
        }
        std::sort(a + 1, a + 1 + acnt), std::sort(b + 1, b + 1 + bcnt);
        aprod[0] = bprod[0] = reaprod[0] = rebprod[0] = 1;
        for (int i = 1; i <= 5 && i <= acnt; ++i) aprod[i] = aprod[i - 1] * a[i];
        for (int i = 1; i <= 5 && i <= bcnt; ++i) bprod[i] = bprod[i - 1] * b[i];
        for (int i = 1; i <= 5 && i <= acnt; ++i) reaprod[i] = reaprod[i - 1] * a[acnt - i + 1];
        for (int i = 1; i <= 5 && i <= bcnt; ++i) rebprod[i] = rebprod[i - 1] * b[bcnt - i + 1];
        for (int i = 0; i <= 5; ++i)
        {
            if (i > acnt || 5 - i > bcnt) continue;
            if (i & 1) res = std::max(res, reaprod[i] * rebprod[5 - i]);
            else res = std::max(res, -aprod[i] * bprod[5 - i]);
        }
        printf("%lld\n", res);
    }
}