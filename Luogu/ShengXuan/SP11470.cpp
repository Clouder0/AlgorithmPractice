#include <cstdio>
#include <algorithm>
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
inline void read(char *s)
{
    static char c;
    for (; !isalpha(c); c = nc());
    for (; isalpha(c); c = nc()) *s++ = c;
    *s = '\0';
}
template<typename T>
inline T read(T &r)
{
    static char c;
    static int flag;
    flag = 1, r = 0;
    for (c = nc(); !isdigit(c); c = nc()) if (c == '-') flag = -1;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r *= flag;
}
const int maxn = 1e5 + 100;
int n, m, a[maxn], root[maxn], L[maxn << 5], R[maxn << 5], ind;
long long sum[maxn << 5],tag[maxn << 5];
inline void pushup(int l, int r, int p) { sum[p] = sum[L[p]] + sum[R[p]] + tag[p] * (r - l + 1); }
void build(int l, int r, int& p)
{
    p = ++ind;
    if (l == r) return (void)(sum[p] = a[l]);
    int mid = l + r >> 1;
    build(l, mid, L[p]), build(mid + 1, r, R[p]), pushup(l, r, p);
}
int modify(int l,int r,int p,int ll,int rr,int k)
{
    int now = ++ind;
    L[now] = L[p],R[now] = R[p],tag[now] = tag[p],sum[now] = sum[p];
    if (l >= ll && r <= rr) return sum[now] += 1ll * (r - l + 1) * k, tag[now] += k, now;
    int mid = l + r >> 1;
    if (ll <= mid) L[now] = modify(l, mid, L[now], ll, rr, k);
    if (rr > mid) R[now] = modify(mid + 1, r, R[now], ll, rr, k);
    pushup(l, r, now);
    return now;
}
long long ask(int l,int r,int p,int ll,int rr)
{
    if (l >= ll && r <= rr) return sum[p];
    int mid = l + r >> 1;
    long long res = 0;
    if (ll <= mid) res = ask(l, mid, L[p], ll, rr);
    if (rr > mid) res += ask(mid + 1, r, R[p], ll, rr);
    return res + 1ll * (std::min(r, rr) - std::max(l, ll) + 1) * tag[p];
}
int main()
{
    read(n),read(m);
    for (int i = 1; i <= n; ++i) read(a[i]);
    build(1, n, root[0]);
    int tim = 0;
    for (int i = 1,l,r,k; i <= m; ++i) 
    {
        static char s[10];
        read(s + 1);
        if (s[1] == 'C') read(l), read(r), read(k), root[tim + 1] = modify(1, n, root[tim], l, r, k), ++tim;
        else if (s[1] == 'Q') read(l), read(r), printf("%lld\n", ask(1, n, root[tim], l, r));
        else if (s[1] == 'H') read(l), read(r), read(k), printf("%lld\n", ask(1, n, root[k], l, r));
        else read(k), tim = k;
    }
    return 0;
}