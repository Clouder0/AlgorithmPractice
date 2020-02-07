#include <cstdio>
#include <cmath>
using namespace std;
template <typename T>
inline T _max(const T &a, const T &b) { return a > b ? a : b; }
template <typename T>
void read(T &r)
{
    static char c;r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar());
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar());
}
const int maxn = 2e7;
bool notprime[maxn];
long long primes[maxn];
int tot;
long long aa, ab, an;
inline void getPrime(long long n)
{
    notprime[1] = true;
    for (int i = 1; i <= n; ++i)
    {
        if (!notprime[i])
            primes[++tot] = i;
        for (int j = 1; j <= tot && primes[j] * i <= n; ++j)
        {
            notprime[i * primes[j]] = true;
            if (i % primes[j] == 0)
                break;
        }
    }
}
long long x;
int main()
{
    read(x);
    an = 1ll << 60;
    long long sx = sqrt(x) * 2;
    getPrime(sx);
    aa = 1,ab = x,an = x;
    for (int i = 1; i <= tot; ++i)
    {
        if (x % primes[i] == 0 && x/primes[i] != primes[i])
        {
            if (_max(primes[i], x / primes[i]) < an)
            {
                aa = primes[i];
                ab = x / primes[i];
                an = _max(primes[i], x / primes[i]);
            }
        }
    }
    printf("%lld %lld", aa, ab);
    return 0;
}