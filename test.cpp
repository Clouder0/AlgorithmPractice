#include <cstdio>
using namespace std;
template <typename T>
inline T read(T &r)
{
    static char c;
    static int flag;
    flag = 1, r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar()) if (c == '-') flag = -1;
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar());
    return r *= flag;
}
const int maxn = 1e5 + 100;
struct node
{
    long long sum, tag;
    int l, r, len, mid;
} a[maxn * 20];
int w[maxn];
int n, m;
inline void push_up(const int &p)
{
    a[p].sum = a[p * 2].sum + a[p * 2 + 1].sum;
}
inline void push_down(const int &p)
{
    node &now = a[p], &ls = a[p * 2], &rs = a[p * 2 + 1];
    if (!now.tag)
        return;
    ls.sum += ls.len * now.tag;
    rs.sum += rs.len * now.tag;
    ls.tag += now.tag;
    rs.tag += now.tag;
    now.tag = 0;
}
void build(const int &l, const int &r, const int &p)
{
    a[p].l = l, a[p].r = r, a[p].len = r - l + 1;
    a[p].mid = (l + r) >> 1;
    if (l == r)
    {
        a[p].sum = w[a[p].l];
        return;
    }
    build(l, a[p].mid, p << 1);
    build(a[p].mid + 1, r, p << 1 | 1);
    push_up(p);
}
void add(const int &p, const int &k, const int &ll, const int &rr)
{
    if (ll <= a[p].l && rr >= a[p].r)
    {
        a[p].sum += a[p].len * k;
        a[p].tag += k;
        return;
    }
    push_down(p);
    if (ll <= a[p].mid)
        add(p << 1, k, ll, rr);
    if (rr > a[p].mid)
        add(p << 1 | 1, k, ll, rr);
    push_up(p);
}
long long ask(const int &p, const int &ll, const int &rr)
{
    if (ll <= a[p].l && rr >= a[p].r)
        return a[p].sum;
    push_down(p);
    long long ans = 0;
    if (ll <= a[p].mid)
        ans = ask(p << 1, ll, rr);
    if (rr > a[p].mid)
        ans += ask(p << 1 | 1, ll, rr);
    return ans;
}
int main()
{
    read(n);
    read(m);
    for(int i = 1;i<=n;++i)
        read(w[i]);
    int nn = 1;
    for(;nn<n;nn*=2);
    build(1, nn, 1);
    int opt, x, y, k;
    while (m--)
    {
        read(opt);
        read(x);
        read(y);
        if (opt == 1)
        {
            read(k);
            add(1, k, x, y);
        }
        else
            printf("%lld\n", ask(1, x, y));
    }
    return 0;
}