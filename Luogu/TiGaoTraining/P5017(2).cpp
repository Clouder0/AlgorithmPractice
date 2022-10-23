#include <cstdio>
#include <cstring>
#define int long long
template <typename T>
inline T _min(const T &a, const T &b) { return a < b ? a : b; }
template <typename T>
void read(T &r)
{
    static char c;
    r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar());
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar());
}
const int maxn = 510;
const int maxt = 4e6 + 10;
int n, m, T;
int a[maxn];
int sum[maxt], cnt[maxt];
int f[maxt];
int q[maxt], head, tail;
inline int gx(int x)
{
    return cnt[x];
}
inline int gy(int x)
{
    return f[x] + sum[x];
}
inline bool cmp1(int x1, int x2, int x3)
{
    return (long long)(gy(x2) - gy(x1)) * (gx(x3) - gx(x2)) >= (long long)(gy(x3) - gy(x2)) * (gx(x2) - gx(x1));
}
inline bool cmp2(int x1, int x2, int k)
{
    return gy(x2) - gy(x1) <= k * (long long)(gx(x2) - gx(x1));
}
signed main()
{
    read(n);
    read(m);
    for (int i = 1; i <= n; ++i)
        read(a[i]), sum[a[i]] += a[i], cnt[a[i]]++, T = (a[i] > T ? a[i] : T);
    T += m;
    for (int i = 1; i <= T; ++i)
        sum[i] += sum[i - 1], cnt[i] += cnt[i - 1];
    int p = 0;
    head = 1;
    for (int i = 0; i <= T; ++i)
    {
        f[i] = cnt[i] * i - sum[i];
        while (p <= i - m && p >= i - m * 2)
        {
            while (tail > head && cmp1(q[tail - 1], q[tail], p))
                --tail;
            q[++tail] = p;
            ++p;
        }
        while (tail >= head && q[head] < i - 2 * m)
            ++head;
        while (tail > head && cmp2(q[head], q[head + 1], i))
            ++head;
        if(tail >= head)
            f[i] = _min(f[i], f[q[head]] + i * (cnt[i] - cnt[q[head]]) - sum[i] + sum[q[head]]);
    }
    int ans = 1 << 30;
    for (int i = T - m; i < T; ++i)
        ans = _min(f[i], ans);
    printf("%lld", ans);
    return 0;
}