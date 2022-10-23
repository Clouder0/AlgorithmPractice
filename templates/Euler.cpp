#include <cstdio>
const int maxn = 1e7 + 100;
int n, p;
bool notprime[maxn];
int primes[maxn], cnt, phi[maxn];
inline void Euler(int top)
{
    phi[1] = 1, notprime[1] = 1;
    for (int i = 2; i <= top; ++i)
    {
        if (!notprime[i]) primes[++cnt] = i, phi[i] = i - 1;
        for (int j = 1; j <= cnt && i * primes[j] <= top; ++j)
        {
            notprime[i * primes[j]] = 1;
            if ((i % primes[j]) == 0) { phi[i * primes[j]] = phi[i] * primes[j]; break; }
            else phi[i * primes[j]] = phi[i] * (primes[j] - 1);
        }
    }
}
int main()
{
    scanf("%d %d", &n, &p);
    Euler(n);
    int ans = 0;
    for (int i = 1; i <= n; ++i) ans = (ans + 1ll * (phi[i] + i) * (phi[i] + i)) % p;
    printf("%d\n", ans);
    return 0;
}