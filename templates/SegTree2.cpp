#include <algorithm>
#include <cstdio>
#include <ctype.h>
const int bufSize = 1e6;
inline char nc()
{
#ifdef DEBUG
    return getchar();
#endif
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
template <typename T>
inline T read(T& r)
{
    static char c;
    static int flag;
    flag = 1, r = 0;
    for (c = nc(); !isdigit(c); c = nc())
        if (c == '-') flag = -1;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r *= flag;
}
const int maxn = 1e5 + 10;

template <const unsigned int _MOD, typename T>
struct ModNum
{
    T x;
    ModNum()
    {
        x = 0;
    }

    template<typename _Tp>
    ModNum(_Tp t)
    {
        x = T(t);
    }

    ModNum(const ModNum& other)
    {
        x = other.x;
    }

    explicit operator T() const
    {
        return x;
    }

    ModNum& operator+=(const ModNum& other)
    {
        x += other.x;
        if (this->x >= _MOD) x -= _MOD;
        return *this;
    }
    ModNum& operator-=(const ModNum& other)
    {
        return *this += _MOD - other.x;
    }
    ModNum& operator*=(const ModNum& other)
    {
        unsigned long long ret = 1ll * x * other.x;
        if (ret >= _MOD) ret %= _MOD;
        this-> x = ret;
        return *this;
    }
   ModNum inv() const
    {
        T a = x, b = _MOD, u = 1, v = 0;
        while (b)
        {
            T t = a / b;
            a -= t * b; std::swap(a, b);
            u -= t * v; std::swap(u, v);
        }
        return ModNum(u);
    }
    ModNum& operator/=(const ModNum& other) { return *this *= other.inv(); }
    friend ModNum operator+(const ModNum& a, const ModNum& b) { return ModNum(a) += b; }
    friend ModNum operator-(const ModNum& a, const ModNum& b) { return ModNum(a) -= b; }
    friend ModNum operator*(const ModNum& a, const ModNum& b) { return ModNum(a) *= b; }
    friend ModNum operator/(const ModNum& a, const ModNum& b) { return ModNum(a) /= b; }
    bool operator==(const ModNum& other) { return x == other.x; }
    bool operator!=(const ModNum& other) { return x != other.x; }
    bool operator<(const ModNum& other) { return x < other.x; }
    bool operator>(const ModNum& other) { return x > other.x; }
    bool operator<=(const ModNum& other) { return x <= other.x; }
    bool operator>=(const ModNum& other) { return x >= other.x; }

    template <typename _Istream>
    friend _Istream& operator>>(_Istream& is, ModNum& self)
    {
        return is >> self.m_val;
    }
    template <typename _Ostream>
    friend _Ostream& operator<<(_Ostream& os, const ModNum& self)
    {
        return os << self.m_val;
    }
};


// Segment Multiply/Add/Query
template <typename T>
struct SegTree
{
#define ls p << 1
#define rs p << 1 | 1
    T a[maxn], sum[maxn << 2], addtag[maxn << 2], multag[maxn << 2];
    inline void pushup(int p)
    {
        sum[p] = sum[ls] + sum[rs];
    }
    inline void pushdown(int l, int r, int p)
    {
        if (multag[p] != 1)
        {
            sum[ls] *= multag[p];
            sum[rs] *= multag[p];
            multag[ls] *= multag[p];
            multag[rs] *= multag[p];
            addtag[ls] *= multag[p];
            addtag[rs] *= multag[p];
            multag[p] = 1;
        }
        if (addtag[p] != 0)
        {
            int mid = (l + r) >> 1;
            sum[ls] += (mid - l + 1) * addtag[p];
            sum[rs] += (r - mid) * addtag[p];
            addtag[ls] += addtag[p];
            addtag[rs] += addtag[p];
            addtag[p] = 0;
        }
    }
    void build(int l, int r, int p)
    {
        addtag[p] = 0, multag[p] = 1;
        if (l == r) return (void)(sum[p] = a[l]);
        int mid = (l + r) >> 1;
        build(l, mid, ls);
        build(mid + 1, r, rs);
        pushup(p);
    }
    void seg_add(int l, int r, int p, int ll, int rr, int k)
    {
        if (l >= ll && r <= rr)
        {
            sum[p] += T(r - l + 1) * k;
            addtag[p] += k;
            return;
        }
        pushdown(l, r, p);
        int mid = (l + r) >> 1;
        if (ll <= mid) seg_add(l, mid, ls, ll, rr, k);
        if (rr > mid) seg_add(mid + 1, r, rs, ll, rr, k);
        pushup(p);
    }
    void seg_mul(int l, int r, int p, int ll, int rr, int k)
    {
        if (l >= ll && r <= rr)
        {
            sum[p] *= k;
            multag[p] *= k;
            addtag[p] *= k;
            return;
        }
        pushdown(l, r, p);
        int mid = (l + r) >> 1;
        if (ll <= mid) seg_mul(l, mid, ls, ll, rr, k);
        if (rr > mid) seg_mul(mid + 1, r, rs, ll, rr, k);
        pushup(p);
    }
    T seg_ask(int l, int r, int p, int ll, int rr)
    {
        if (l >= ll && r <= rr) return sum[p];
        int mid = (l + r) >> 1;
        pushdown(l, r, p);
        if (ll <= mid && rr > mid) return seg_ask(l, mid, ls, ll, rr) + seg_ask(mid + 1, r, rs, ll, rr);
        if (ll <= mid) return seg_ask(l, mid, ls, ll, rr);
        return seg_ask(mid + 1, r, rs, ll, rr);
    }
};
SegTree<ModNum<571373, unsigned int>> T;
int n, m, p, a[maxn];
signed main()
{
    read(n), read(m), read(p);
    for (int i = 1; i <= n; ++i) read(a[i]), a[i] %= 571373;
    for (int i = 1; i <= n; ++i) T.a[i] = a[i];
    T.build(1, n, 1);
    while (m--)
    {
        int opt, x, y, k;
        read(opt), read(x), read(y);
        if (opt == 1)
        {
            read(k);
            k %= 571373;
            T.seg_mul(1, n, 1, x, y, k);
        }
        else if (opt == 2)
        {
            read(k);
            k %= 571373;
            T.seg_add(1, n, 1, x, y, k);
        }
        else
        {
            printf("%d\n", T.seg_ask(1, n, 1, x, y).x);
        }
    }
    return 0;
}