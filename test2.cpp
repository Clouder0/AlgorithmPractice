#include <cstdio>
using namespace std;
template <typename T>
inline T read(T &r)
{
    static char c;
    static int flag;
    flag = 1, r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar())
        if (c == '-')
            flag = -1;
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar())
        ;
    return r *= flag;
}
const int maxn = 1e5 + 100;
struct node
{
    long long sum, tag;
    int l, r, len, lmid, rmid; //[l,lmid],[lmid+1,rmid],[rmid+1,r]
} a[maxn * 20];
int w[maxn];
int n, m;
inline void push_up(const int &p)
{
    a[p].sum = a[p * 3].sum + a[p * 3 + 1].sum + a[p * 3 + 2].sum;
}
inline void push_down(const int &p)
{
    node &now = a[p], &ls = a[p * 3], &ms = a[p * 3 + 1], &rs = a[p * 3 + 2];
    if (!now.tag)
        return;
    ls.sum += ls.len * now.tag;
    ms.sum += ms.len * now.tag;
    rs.sum += rs.len * now.tag;
    ls.tag += now.tag;
    ms.tag += now.tag;
    rs.tag += now.tag;
    now.tag = 0;
}
void build(const int &l, const int &r, const int &p)
{
    a[p].l = l, a[p].r = r, a[p].len = r - l + 1;
    int len = a[p].len / 3;
    a[p].lmid = a[p].l + len - 1;
    a[p].rmid = a[p].lmid + len;
    if (l == r)
    {
        a[p].lmid = a[p].rmid = a[p].l;
        a[p].sum = w[l];
        return;
    }
    build(l, a[p].lmid, p * 3);
    build(a[p].lmid + 1, a[p].rmid, p * 3 + 1);
    build(a[p].rmid + 1, a[p].r, p * 3 + 2);
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
    if (ll > a[p].r)
        return;
    if (rr < a[p].l)
        return;
    int lp = 0;
    if (ll <= a[p].lmid)
        add(p * 3, k, ll, rr), lp = 1;
    else if (ll <= a[p].rmid)
        add(p * 3 + 1, k, ll, rr), lp = 2;
    else
        add(p * 3 + 2, k, ll, rr), lp = 3;
    if (rr > a[p].rmid && lp != 3)
        add(p * 3 + 2, k, ll, rr);
    else if (rr > a[p].lmid && lp != 2)
        add(p * 3 + 1, k, ll, rr);
    else if (lp != 1)
        add(p * 3, k, ll, rr);
    if (lp == 1 && rr > a[p].rmid)
        add(p * 3 + 1, k, ll, rr);
    push_up(p);
}
long long ask(const int &p, const int &ll, const int &rr)
{
    if (ll <= a[p].l && rr >= a[p].r)
        return a[p].sum;
    if (ll > a[p].r)
        return 0;
    if (rr < a[p].l)
        return 0;
    push_down(p);
    long long ans = 0;
    int lp = 0;
    if (ll <= a[p].lmid)
        ans += ask(p * 3, ll, rr), lp = 1;
    else if (ll <= a[p].rmid)
        ans += ask(p * 3 + 1, ll, rr), lp = 2;
    else
        ans += ask(p * 3 + 2, ll, rr), lp = 3;
    if (rr > a[p].rmid && lp != 3)
        ans += ask(p * 3 + 2, ll, rr);
    else if (rr > a[p].lmid && lp != 2)
        ans += ask(p * 3 + 1, ll, rr);
    else if (lp != 1)
        ans += ask(p * 3, ll, rr);
    if (lp == 1 && rr > a[p].rmid)
        ans += ask(p * 3 + 1, ll, rr);
    return ans;
}
int main()
{
    read(n);
    read(m);
    for (int i = 1; i <= n; ++i)
        read(w[i]);
    int nn = 1;
    for (nn = 1; nn < n; nn *= 3)
        ;
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