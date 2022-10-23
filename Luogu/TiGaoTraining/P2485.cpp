#include <cstdio>
#include <map>
#include <cstring>
#include <cmath>
using namespace std;
#define ll long long
#define int long long
int T,K;
ll y,z,p;
ll mul(ll a,ll b,ll mod)
{
    ll res = 0;
    while(b)
    {
        if(b & 1) res = (res + a) % mod;
        a = (a + a) % mod;
        b >>= 1;
    }
    return ((res % mod) + mod) % mod;
}
ll fastpow(ll x,ll k,ll mod)
{
    ll res = 1;
    for (; k; k >>= 1)
    {
        if (k & 1) res = mul(res,x,mod);
        x = mul(x,x,mod);
    }
    return res;
}
ll exgcd(ll a,ll b,ll &x,ll &y)
{
    if (b == 0) { x = 1, y = 0; return a; }
    ll g = exgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return g;
}
struct BetterListHashTable
{
    static const int mod = 1000103;
    static const int maxn = 1e6 + 100;
    struct node
    {
        int next, key, val;
    } A[maxn + 10];
    int head[mod + 100],tot;
    void clear(){memset(head,0,sizeof(head)),tot = 0;}
    int hash(int x)
    {
        int res = x % mod;
        if (res < 0) res += mod;
        return res;
    }
    int & operator [](int key)
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
        for(int p = head[pos];p;p=A[p].next)
            if(A[p].key == key) return &A[p].val;
        return NULL;
    }
}HT;
signed main()
{
    scanf("%d %d",&T,&K);
    while(T--)
    {
        scanf("%lld %lld %lld",&y,&z,&p);
        if(K == 1) printf("%lld\n",fastpow(y,z,p));
        else if(K == 2) 
        {
            //yx + pk = z
            ll a = y, b = p, c = z,k1,k2;
            ll g = exgcd(a,b,k1,k2);
            if(c % g) {puts("Orz, I cannot find x!");continue;}
            k1 *= c / g;
            ll t = b / g;
            k1 = ((k1 % t) + t) % t;
            printf("%lld\n", k1);
        }
        else if(K == 3)
        {
            HT.clear();
            ll sqrtp = std::ceil(std::sqrt(p));
            y %= p,z %= p;
            if(y == 0) {puts("Orz, I cannot find x!");continue;}
            ll t = z;
            for (int i = 0; i <= sqrtp; ++i)
                HT[t] = i, t = mul(t, y, p);
            ll sq = fastpow(y,sqrtp,p);
            t = sq;
            for (int i = 1; i <= sqrtp; ++i)
            {
                int *ans = HT.find(t);
                if(ans != NULL)
                {
                    printf("%lld\n", 1ll * i * sqrtp - *ans);
                    goto end;
                }
                t = (t * sq) % p;
            }
            puts("Orz, I cannot find x!");
            end:;
        }
    }
    return 0;
}