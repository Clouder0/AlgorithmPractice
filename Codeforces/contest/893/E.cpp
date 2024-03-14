#include <cstdio>

const int mod = 1e9 + 7;
inline int add(int a,int b) {return a + b >= mod ? a + b - mod : a + b;}
inline int mul(int a, int b) {long long res = 1ll * a * b; return res >= mod ? res % mod : res;}
int q, x, y;
int p[40], k[40], cnt;
int primes[1000100], num, notprime[1001000];
int fastpow(int x,int k) {
    int res = 1;
    while(k > 0) {
        if(k & 1) res = mul(res, x);
        x = mul(x,x);
        k>>=1;
    }
    return res;
}
const int maxn = 2e6 + 100;
int prod[maxn],invs[maxn];
int inv[maxn];
void init()
{
    inv[0] = 1, inv[1] = 1;
    for (int i = 2; i <= 2000000; ++i) inv[i] = 1ll * (mod - mod / i) * inv[mod % i] % mod;
    prod[0] = 1;
    for(int i = 1;i<=2000000;++i) prod[i] = mul(prod[i-1],i);
    invs[0] = 1, invs[1] = 1;
    for(int i = 2;i<=2000000;++i) invs[i] = mul(invs[i-1],inv[i]);
}

int select(int n, int m) {
    return mul(prod[n], mul(invs[m], invs[n - m]));
}
int main()
{
    scanf("%d", &q);
    init();
    for (int i = 2; i <= 1000000; ++i)
    {
        if (!notprime[i]) primes[++num] = i;
        for (int j = 1; j <= num && i * primes[j] <= 1000000; ++j)
        {
            notprime[i * primes[j]] = 1;
            if (i % primes[j] == 0) break;
        }
    }
    while (q--)
    {
        scanf("%d%d", &x, &y);
        cnt = 0;
        for (int i = 1; i <= num && primes[i] * primes[i] <= x; ++i)
        {
            if (x % primes[i] == 0)
            {
                p[++cnt] = primes[i];
                k[cnt] = 0;
                while (x % primes[i] == 0) x /= primes[i], ++k[cnt];
            }
        }
        if(x != 1) p[++cnt] = x, k[cnt] = 1;
        // printf("cnt%d, p[1]=%d, k[1]=%d\n",cnt,p[1],k[1]);
        long long res = 1;
        for(int i = 1;i<=cnt;++i) {
            res = mul(res, select(k[i] + y - 1, y - 1));
        }
        res = mul(res,fastpow(2, y - 1));
        printf("%lld\n",res);
    }
    return 0;
}