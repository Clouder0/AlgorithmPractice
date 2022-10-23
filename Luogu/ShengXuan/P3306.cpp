#include <cstdio>
#include <cmath>
#include <cstring>
#define ll long long
int T;
ll p,a,b,x1,t;
ll fastpow(ll x,ll k)
{
    ll res = 1;
    while(k)
    {
        if(k & 1) res = (res * x) % p;
        x = (x * x) % p;
        k >>= 1;
    }
    return ((res % p) + p) % p;
}
ll inv(ll x) { return fastpow(x, p - 2); }
struct BetterListHashTable
{
    static const int mod = 100103;
    static const int maxn = 2e5 + 100;
    struct node
    {
        int next, key, val;
    } A[maxn + 10];
    int head[mod + 100], tot;
    void clear() { memset(head, 0, sizeof(head)), tot = 0; }
    int hash(int x)
    {
        int res = x % mod;
        if (res < 0) res += mod;
        return res;
    }
    int& operator[](int key)
    {
        int pos = hash(key);
        for (int p = head[pos]; p; p = A[p].next)
            if (A[p].key == key) return A[p].val;
        A[++tot].next = head[pos], A[tot].key = key, A[tot].val = 0, head[pos] = tot;
        return A[tot].val;
    }
    int* find(int key)
    {
        int pos = hash(key);
        for (int p = head[pos]; p; p = A[p].next)
            if (A[p].key == key) return &A[p].val;
        return NULL;
    }
} HT;
ll exgcd(ll a,ll b,ll &x,ll &y)
{
    if(b == 0){x = 1,y = 0;return a;}
    ll g = exgcd(b,a%b,y,x);y -= (a / b) * x;
    return g;
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%lld %lld %lld %lld %lld", &p, &a, &b, &x1, &t);
        if(x1 == t) {puts("1");continue;}
        if(a == 1 && b == 0) {puts("-1");continue;}
        if(a == 0)
        {
            if(b == t) {puts("2");continue;}
            puts("-1");continue;
        }
        if(a == 1)
        {
        //t = x_1 + (i-1) \times b + k \times p
        //t - x_1 = (i-1) \times b + k2 \times p
            ll k1,k2,g;
            g = exgcd(b,p,k1,k2);
            ll c = (((t - x1) % p) + p) % p;
            if(c % g) {puts("-1");continue;}
            k1 = (((k1 * c / g % p) + p) % p) + 1;
            printf("%lld\n", k1);
            continue;
        }
        HT.clear();
        ll c = (b * inv(a - 1)) % p;
        ll C = ((t + c) * inv(x1 + c)) % p;
        ll sqrtp = std::ceil(std::sqrt(p));
        ll tmp = C;
        for (int i = 0; i <= sqrtp; ++i) HT[tmp] = i, tmp = (tmp * a) % p;
        ll sq = fastpow(a,sqrtp);
        tmp = sq;
        for (int i = 1; i <= sqrtp; ++i)
        {
            int* ans = HT.find(tmp);
            if(ans != NULL) { printf("%lld\n",i * sqrtp - *ans + 1); goto end; }
            tmp = (tmp * sq) % p;
        }
        puts("-1");
    end:;
    }
    return 0;
}