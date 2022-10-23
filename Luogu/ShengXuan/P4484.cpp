#include <cstdio>
#include <cmath>
#define ll long long
#define int long long
ll K,m;
inline ll mul(ll a,ll b,ll mod)
{
    ll res = 0;
    while(b)
    {
        if(b & 1) res = (res + a) % mod;
        a = (a + a) % mod;
        b >>= 1;
    }
    return (res + mod) % mod;
}
const int maxn = 5e6 + 100;
const int hashmod = 300123;
namespace HT
{
    int head[hashmod + 100],nex[maxn],key[maxn],val[maxn],tot;
    inline int hash(const ll &x)
    {
        int res = x % hashmod;
        if(res < 0) res += hashmod;
        return res;
    }
    int* find(ll x)
    {
        int pos = hash(x);
        for (int p = head[pos]; p; p = nex[p])
            if (key[p] == x) return &val[p];
        return NULL;
    }
    void set(ll x,int v)
    {
        int pos = hash(x);
        for (int p = head[pos]; p; p = nex[p])
            if (key[p] == x) return (void)(val[p] = v);
        ++tot, nex[tot] = head[pos], key[tot] = x, val[tot] = v, head[pos] = tot;
    }
}
inline ll fastpow(ll x,ll k,ll mod)
{
    ll res = 1;
    while(k)
    {
        if (k & 1) res = mul(res, x, mod);
        x = mul(x, x, mod);
        k >>= 1;
    }
    return res;
}
signed main()
{
    scanf("%lld %lld",&K,&m);
    K = (K * 9 + 1) % m;
    ll sqrtm = std::ceil(std::sqrt(m));
    ll t = K;
    for (int i = 0; i <= sqrtm; ++i)
    {
        HT::set(t,i);
        t = mul(t,10,m);
    }
    ll sq = fastpow(10, sqrtm, m);
    t = sq;
    for (int i = 1; i <= sqrtm; ++i)
    {
        int* p = HT::find(t);
        if(p != NULL)
        {
            printf("%lld\n", 1ll * i * sqrtm - *p);
            return 0;
        }
        t = mul(t,sq,m);
    }
    return 0;
}