#include <cstdio>
#include <algorithm>
template <typename T>
void read(T &r)
{
    static char c;r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar());
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar());
}
const int maxn = 1000000;
long long n, ans;
long long A[maxn], tot;
inline long long calc(long long x){return x - x / 2 - x / 5 + x / 10;}
int main()
{
    read(n);
    for (long long i = 1; i <= n; i <<= 1)
        for (long long j = 1; i * j <= n; j *= 5)
            A[++tot] = i * j;
    std::sort(A + 1, A + 1 + tot);
    long long l, r, k;
    for (long long l = 1; l <= n; l = r + 1)
    {
        k = n / l, r = n / k;
        while (l * A[tot] > n && tot) --tot;
        ans = ans + k * (calc(r) - calc(l - 1)) * tot;
    }
    printf("%lld", ans);
    return 0;
}