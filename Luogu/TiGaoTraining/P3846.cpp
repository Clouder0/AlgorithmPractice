#include <cstdio>
#include <cmath>
#include <cstring>
#define ll long long
ll fastpow(ll x,ll k,ll mod)
{
    ll res = 1;
    for (; k; k >>= 1)
    {
        if (k & 1) res = (res * x) % mod;
        x = (x * x) % mod;
    }
    return ((res % mod) + mod) % mod;
}
struct BetterListHashTable
{
    static const int mod = 100103;
    static const int maxn = 1e6 + 100;
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
inline ll BSGS(ll A, ll B, ll P)
{
    //A^x = B (mod P) (A,P) = 1
    HT.clear();
    ll t = B;
    ll sqrtp = std::ceil(std::sqrt(P));
    for (int i = 0; i <= sqrtp; ++i) HT[t] = i, t = (t * A) % P;
    ll sq = fastpow(A, sqrtp, P);
    t = sq;
    for (int i = 1; i <= sqrtp; ++i)
    {
        int* ans = HT.find(t);
        if (ans != NULL) return i * sqrtp - *ans;
        t = (t * sq) % P;
    }
    return -1;
}
ll gcd(ll a,ll b){return b == 0 ? a : gcd(b,a%b);}
void exgcd(ll a,ll b,ll &x,ll &y)
{
    if (b == 0) return (void)(x = 1, y = 0);
    exgcd(b, a % b, y, x), y -= (a / b) * x;
}
ll inv(ll x,ll P)
{
    //xinv + Pk = 1
    ll k1,k2;
    exgcd(x,P,k1,k2);
    k1 = ((k1 % P) + P) % P;
    return k1;
}
inline ll exBSGS(ll A,ll B,ll P)
{
    ll m = 0,D = 1,g;
    if(B == 1) return 0;
    while((g = gcd(A,P)) != 1)
    {
        if (B % g) return -1;
        P /= g, ++m;
    }
    B = (B * inv(fastpow(A, m, P),P)) % P;//inv(a^m)
    ll res = BSGS(A,B,P);
    if(res == -1) return -1;
    return res + m;
}
int main()
{
    ll a,b,p;
    scanf("%lld %lld %lld",&p,&a,&b);
        ll res = exBSGS(a,b,p);
        if(res == -1) puts("no solution");
        else printf("%lld\n",res);
    return 0;
}