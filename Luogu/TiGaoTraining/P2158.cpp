#include <cstdio>
const int maxn = 4e4 + 100;
bool notprime[maxn];
int primes[maxn], cnt, phi[maxn];
int n;
inline void euler()
{
    for (int i = 2; i <= n - 1; ++i)
    {
        if (!notprime[i]) primes[++cnt] = i, phi[i] = i - 1;
        for (int j = 1; j <= cnt && primes[j] * i <= n - 1; ++j)
        {
            notprime[i * primes[j]] = 1;
            if ((i % primes[j]) == 0) { phi[i * primes[j]] = phi[i] * primes[j]; break; }
            phi[i * primes[j]] = phi[i] * (primes[j] - 1);
        }
    }
}
int main()
{
    scanf("%d", &n);
    euler();
    long long ans = 0;
    for (int i = 2; i < n; ++i) ans += phi[i];
    ans = ans * 2 + 3;
    if(n == 1) ans = 0;
    printf("%lld\n",ans);
    return 0;
}