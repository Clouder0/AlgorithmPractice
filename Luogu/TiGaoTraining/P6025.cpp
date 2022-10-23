#include <cstdio>
#include <cstring>
using namespace std;
#define ll long long
struct BetterListHashTable
{
    static const int mod = 1000103;
    static const int maxn = 1e6 + 100;
    struct node
    {
        int next, val;
        ll key;
    } A[maxn + 10];
    int head[mod + 100],tot;
    void clear()
    {
        memset(head,0,sizeof(head)),tot = 0;
    }
    int hash(ll x)
    {
        int res = x % mod;
        if (res < 0) res += mod;
        return res;
    }
    int & operator [](ll key)
    {
        int pos = hash(key);
        for (int p = head[pos]; p; p = A[p].next)
            if (A[p].key == key) return A[p].val;
        A[++tot].next = head[pos], A[tot].key = key, A[tot].val = 0, head[pos] = tot;
        return A[tot].val;
    }
    int* find(ll key)
    {
        int pos = hash(key);
        for(int p = head[pos];p;p=A[p].next)
            if(A[p].key == key) return &A[p].val;
        return NULL;
    }
}H;
ll l,r;
int lg(ll x)
{
    int l = 0,r = 62,mid,ans = 0;
    while(l <= r)
    {
        mid = l + r >> 1;
        if((1ll << mid) <= x) l = mid + 1;
        else ans = mid,r = mid - 1;
    }
    return ans;
}
bool ispow(ll x){return !(x & (x - 1));}
ll solve(ll n,ll dep) 
{
    if(ispow(n) || ispow(n - 1)) return n * 2 - 1;
    return (1ll << dep) + solve(n / 2,dep - 1);
}
ll get(ll n)
{
    if(n == 0) return 0;
    ll res = 0;
    H.clear();
    for(ll i = 1;i <= n;i *= 2)
    {
        if(H.find(i) == NULL) H[i] = 1,res ^= solve(i,lg(i));
        if (i < n && H.find(i + 1) == NULL) H[i + 1] = 1, res ^= solve(i + 1, lg(i));
    }
    if (!(n & 1) && H.find(n) == NULL) res ^= solve(n, lg(n));
    return res;
}
int main()
{
    scanf("%lld %lld",&l,&r);
    printf("%lld\n",get(l - 1) ^ get(r));
    return 0;
}