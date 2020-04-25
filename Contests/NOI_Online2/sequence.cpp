#include <cstdio>
#include <map>
const int bufSize = 1e6;
inline char nc()
{
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
template <typename T>
void read(T &r)
{
    static char c;
    r = 0;
    for (c = nc(); c > '9' || c < '0'; c = nc());
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = nc());
}
const int maxn = 1e6;
const int mod = 1e9 + 7;
int n;
long long a[maxn];
std::map<long long, int> last;
int next[maxn];
long long sum[maxn << 2], tag[maxn << 2], qsum[maxn << 2];
inline void push_up(const int &p)
{
    qsum[p] = qsum[p << 1] + qsum[p << 1 | 1];
    sum[p] = sum[p << 1] + sum[p << 1 | 1];
}
inline void push_down(const int &l, const int &r, const int &p)
{
    if (!tag[p])
        return;
    int mid = l + r >> 1;
    tag[p << 1] = (tag[p << 1] + tag[p]) % mod;
    tag[p << 1 | 1] = (tag[p << 1 | 1] + tag[p]) % mod;
    qsum[p << 1] = (qsum[p << 1] + (long long)tag[p] * tag[p] * (mid - l + 1)) % mod;
    qsum[p << 1] = (qsum[p << 1] + tag[p] * 2 * sum[p << 1]) % mod;
    qsum[p << 1 | 1] = (qsum[p << 1 | 1] + tag[p] * tag[p] * (r - mid)) % mod;
    qsum[p << 1 | 1] = (qsum[p << 1 | 1] + tag[p] * 2 * sum[p << 1 | 1]) % mod;
    sum[p << 1] = (sum[p << 1] + (mid - l + 1) * tag[p]) % mod;
    sum[p << 1 | 1] = (sum[p << 1 | 1] + (r - mid) * tag[p]) % mod;
    tag[p] = 0;
}
void modify(const int &l, const int &r, const int &p, const int &ll, const int &rr, const int &k)
{
    if (ll <= l && rr >= r)
    {
        qsum[p] += k * k * (r - l + 1);
        qsum[p] += k * 2 * sum[p];
        sum[p] += (r - l + 1) * k;
        tag[p] += k;
        return;
    }
    push_down(l, r, p);
    int mid = l + r >> 1;
    if (ll <= mid)
        modify(l, mid, p << 1, ll, rr, k);
    if (rr > mid)
        modify(mid + 1, r, p << 1 | 1, ll, rr, k);
    push_up(p);
}
long long ask(const int &l, const int &r, const int &p, const int &ll, const int &rr)
{
    if (ll <= l && rr >= r)
        return qsum[p];
    push_down(l, r, p);
    int mid = l + r >> 1;
    long long ans = 0;
    if (ll <= mid)
        ans += ask(l, mid, p << 1, ll, rr);
    if (rr > mid)
        ans += ask(mid + 1, r, p << 1 | 1, ll, rr);
    return ans;
}
int main()
{
    freopen("sequence.in", "r", stdin);
    freopen("sequence.out", "w", stdout);
    read(n);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    long long ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        int siz = last.size();
        int t = last[a[i]];
        if (t == 0)
            siz++;
        modify(1, n, 1, i, i, siz);
        ans = (ans + siz * siz) % mod;
        if (t)
            next[t] = i;
        last[a[i]] = i;
    }
    for (int i = 1; i < n; ++i)
    {
        //弹出I
        if (next[i])
        {
            modify(1, n, 1, i + 1, next[i] - 1, -1);
            ans = (ans + ask(1, n, 1, i + 1, n)) % mod;
        }
        else
        {
            modify(1, n, 1, i + 1, n, -1);
            ans = (ans + ask(1, n, 1, i + 1, n)) % mod;
        }
    }
    printf("%lld", (ans + mod) % mod);
    return 0;
}