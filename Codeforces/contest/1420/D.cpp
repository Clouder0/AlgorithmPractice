#include <cstdio>
#include <algorithm>
#define int long long
using namespace std;
const int maxn = 1e6 + 100;
int n,k;
struct node
{
    int l,r;
}A[maxn];
int H[maxn],cnt;
const int mod = 998244353;
int prod[maxn],prodinv[maxn];
void exgcd(int a,int b,int &x,int &y)
{
    if(!b) return (void)(x = 1,y = 0);
    exgcd(b,a%b,y,x),y -= (a / b) * x;
}
int inv(int x)
{
    int k1,k2;
    exgcd(x,mod,k1,k2),k1 %= mod;
    if(k1 < 0) k1 += mod;
    return k1;
}
int C(int n,int m)
{
    if(!m) return 1;
    if(n == m) return 1;
    if(n < m) return 0;
    return (((1ll * prod[n] * prodinv[m]) % mod) * prodinv[n - m]) % mod;
}
bool cmp(const node& a, const node& b) { return a.l == b.l ? a.r < b.r : a.l < b.l; }
int sum[maxn];
inline int lowbit(int x){return x & -x;}
inline void add(int x, int k) { for (; x <= cnt; x += lowbit(x)) sum[x] += k; }
inline int ask(int x)
{
    int res = 0;
    for(;x > 0;x-=lowbit(x)) res += sum[x];
    return res;
}
signed main()
{
    scanf("%lld %lld",&n,&k);
    prod[0] = 1;
    for (int i = 1; i <= n; ++i) prod[i] = (1ll * prod[i-1] * i) % mod;
    for (int i = 1; i <= n; ++i) prodinv[i] = inv(prod[i]);
    for (int i = 1; i <= n; ++i) scanf("%lld %lld",&A[i].l,&A[i].r),H[++cnt] = A[i].l,H[++cnt] = A[i].r;
    sort(H + 1,H + 1 + cnt),cnt = unique(H + 1,H + 1 + cnt) - H - 1;
    for (int i = 1; i <= n; ++i) 
        A[i].l = lower_bound(H + 1, H + 1 + cnt, A[i].l) - H, A[i].r = lower_bound(H + 1, H + 1 + cnt, A[i].r) - H;
    sort(A + 1,A + 1 + n,cmp);
    long long ans = 0;
    for (int i = 1; i <= n; ++i) 
    {
        int num = ask(cnt) - ask(A[i].l - 1);
        if (num >= k - 1) ans = (ans + C(num, k - 1)) % mod;
        add(A[i].r,1);
    }
    printf("%lld\n",ans);
    return 0;
}