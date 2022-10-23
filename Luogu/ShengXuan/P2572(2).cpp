#include <cstdio>
using namespace std;
template <typename T>
void read(T &r)
{
    static char c;
    r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar())
        ;
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar())
        ;
}
template <typename T>
inline T min(const T &a, const T &b) { return a < b ? a : b; }
template <typename T>
inline T max(const T &a, const T &b) { return a > b ? a : b; }
template <typename T>
inline void swap(T &x, T &y)
{
    T t;
    t = x;
    x = y;
    y = t;
}
const int maxn = 1e5 + 10;
int n, m, l, r, flag;
int sum[maxn << 2], max0[maxn << 2], max1[maxn << 2], lmax0[maxn << 2], lmax1[maxn << 2], rmax0[maxn << 2], rmax1[maxn << 2];
int lazy[maxn << 2], rev[maxn << 2];
inline void push_up(const int &l, const int &r, const int &p)
{
    int mid = (l + r) >> 1;
    int ls = p << 1, rs = (p << 1) | 1;

    max0[p] = max(max0[ls], max0[rs]);
    max0[p] = max(max0[p], rmax0[ls] + lmax0[rs]);
    max1[p] = max(max1[ls], max1[rs]);
    max1[p] = max(max1[p], rmax1[ls] + lmax1[rs]);
    sum[p] = sum[ls] + sum[rs];
    if (sum[ls] == 0)
        lmax1[p] = 0, lmax0[p] = mid - l + 1 + lmax0[rs];
    else if (sum[ls] == mid - l + 1)
        lmax0[p] = 0, lmax1[p] = mid - l + 1 + lmax1[rs];
    else
        lmax0[p] = lmax0[ls], lmax1[p] = lmax1[ls];

    if (sum[rs] == 0)
        rmax1[p] = 0, rmax0[p] = r - mid + rmax0[ls];
    else if (sum[rs] == r - mid)
        rmax0[p] = 0, rmax1[p] = r - mid + rmax1[ls];
    else
        rmax0[p] = rmax0[rs], rmax1[p] = rmax1[rs];
    ++mid; //for debug
}
inline void push_down(const int &l, const int &r, const int &p)
{
    int mid = (l + r) >> 1, ls = p << 1, rs = p << 1 | 1;
    if (lazy[p] != -1)
    {
        lazy[ls] = lazy[rs] = lazy[p];
        rev[p] = 0;
        if (lazy[p] == 0)
        {
            sum[ls] = sum[rs] = 0;
            lmax0[ls] = rmax0[ls] = max0[ls] = mid - l + 1;
            lmax0[rs] = rmax0[rs] = max0[rs] = r - mid;
            lmax1[ls] = rmax1[ls] = lmax1[rs] = rmax1[rs] = max1[ls] = max1[rs] = 0;
        }
        else
        {
            sum[ls] = lmax1[ls] = rmax1[ls] = max1[ls] = mid - l + 1;
            sum[rs] = lmax1[rs] = rmax1[rs] = max1[rs] = r - mid;
            lmax0[ls] = rmax0[ls] = lmax0[rs] = rmax0[rs] = max0[ls] = max0[rs] = 0;
        }
        lazy[p] = -1;
        return;
    }
    if (rev[p])
    {
        if (lazy[ls] != -1)
            lazy[ls] ^= 1;
        else
            rev[ls] ^= 1;
        if (lazy[rs] != -1)
            lazy[rs] ^= 1;
        else
            rev[rs] ^= 1;
        swap(lmax0[ls], lmax1[ls]);
        swap(rmax0[ls], rmax1[ls]);
        swap(max0[ls], max1[ls]);
        sum[ls] = mid - l + 1 - sum[ls];

        swap(lmax0[rs], lmax1[rs]);
        swap(rmax0[rs], rmax1[rs]);
        swap(max0[rs], max1[rs]);
        sum[rs] = r - mid - sum[rs];
        rev[p] = 0;
        return;
    }
}
inline void build(const int &l, const int &r, const int &p)
{
    lazy[p] = -1;
    if (l == r)
    {
        int temp;
        read(temp);
        if (temp == 0)
        {
            max0[p] = lmax0[p] = rmax0[p] = 1;
            sum[p] = lmax1[p] = rmax1[p] = max1[p] = 0;
        }
        else
        {
            max1[p] = lmax1[p] = rmax1[p] = sum[p] = 1;
            max0[p] = lmax0[p] = rmax0[p] = 0;
        }
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, p << 1);
    build(mid + 1, r, p << 1 | 1);
    push_up(l, r, p);
}
int ll, rr, k;
inline void set0(const int &l, const int &r, const int &p)
{
    if (ll <= l && rr >= r)
    {
        sum[p] = lmax1[p] = rmax1[p] = max1[p] = 0;
        lmax0[p] = rmax0[p] = max0[p] = r - l + 1;
        lazy[p] = 0;
        rev[p] = 0;
        return;
    }
    push_down(l, r, p);
    int mid = (l + r) >> 1;
    if (ll <= mid)
        set0(l, mid, p << 1);
    if (rr > mid)
        set0(mid + 1, r, p << 1 | 1);
    push_up(l, r, p);
}
inline void set1(const int &l, const int &r, const int &p)
{
    if (ll <= l && rr >= r)
    {
        lmax0[p] = rmax0[p] = max0[p] = 0;
        sum[p] = lmax1[p] = rmax1[p] = max1[p] = r - l + 1;
        lazy[p] = 1;
        rev[p] = 0;
        return;
    }
    push_down(l, r, p);
    int mid = (l + r) >> 1;
    if (ll <= mid)
        set1(l, mid, p << 1);
    if (rr > mid)
        set1(mid + 1, r, p << 1 | 1);
    push_up(l, r, p);
}
inline void reverse(const int &l, const int &r, const int &p)
{
    if (ll <= l && rr >= r)
    {
        swap(lmax0[p], lmax1[p]);
        swap(rmax0[p], rmax1[p]);
        swap(max0[p], max1[p]);
        sum[p] = r - l + 1 - sum[p];
        rev[p] = 1;
        return;
    }
    push_down(l, r, p);
    int mid = (l + r) >> 1;
    if (ll <= mid)
        reverse(l, mid, p << 1);
    if (rr > mid)
        reverse(mid + 1, r, p << 1 | 1);
    push_up(l, r, p);
}
inline int ask(const int &l, const int &r, const int &p)
{

    if (ll <= l && rr >= r)
        return sum[p];
    push_down(l, r, p);
    int ans = 0;
    int mid = (l + r) >> 1;
    if (ll <= mid)
        ans += ask(l, mid, p << 1);
    if (rr > mid)
        ans += ask(mid + 1, r, p << 1 | 1);
    return ans;
}
struct result
{
    int lmax0, lmax1, rmax0, rmax1, max0, max1, sum, l, r;
};
inline result askCon(const int &l, const int &r, const int &p)
{
    push_down(l, r, p);
    if (ll <= l && rr >= r)
        return (result){lmax0[p], lmax1[p], rmax0[p], rmax1[p], max0[p], max1[p], sum[p], l, r};
    int mid = (l + r) >> 1;
    if (ll > mid)
        return askCon(mid + 1, r, p << 1 | 1);
    if (rr <= mid)
        return askCon(l, mid, p << 1);
    result al, ar, res;
    al = askCon(l, mid, p << 1);
    ar = askCon(mid + 1, r, p << 1 | 1);
    res.l = l,res.r = r;
    res.sum = al.sum + ar.sum;
    res.max0 = max(al.max0, ar.max0);
    res.max0 = max(al.rmax0 + ar.lmax0, res.max0);
    res.max1 = max(al.max1, ar.max1);
    res.max1 = max(al.rmax1 + ar.lmax1, res.max1);
    if (al.sum == al.r - al.l + 1)
    {
        res.lmax0 = 0;
        res.lmax1 = al.r - al.l + 1 + ar.lmax1;
    }
    else if (al.sum == 0)
    {
        res.lmax1 = 0;
        res.lmax0 = al.r - al.l + 1 + ar.lmax0;
    }
    else
    {
        res.lmax0 = al.lmax0;
        res.lmax1 = al.lmax1;
    }

    if (ar.sum == ar.r - ar.l + 1)
    {
        res.rmax0 = 0;
        res.rmax1 = ar.r - ar.l + 1 + al.rmax1;
    }
    else if (ar.sum == 0)
    {
        res.rmax1 = 0;
        res.rmax0 = ar.r - ar.l + 1 + al.rmax0;
    }
    else
    {
        res.rmax0 = ar.rmax0;
        res.rmax1 = ar.rmax1;
    }
    return res;
}
int main()
{
    read(n);
    read(m);
    build(1, n, 1);
    while (m--)
    {
        read(flag);
        read(ll);
        read(rr);
        ++ll, ++rr;
        switch (flag)
        {
        case 0:
            set0(1, n, 1);
            break;
        case 1:
            set1(1, n, 1);
            break;
        case 2:
            reverse(1, n, 1);
            break;
        case 3:
            printf("%d\n", ask(1, n, 1));
            break;
        case 4:
            printf("%d\n", askCon(1, n, 1).max1);
            break;
        }
    }
    return 0;
}