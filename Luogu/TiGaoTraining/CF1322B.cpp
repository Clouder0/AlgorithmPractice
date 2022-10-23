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
    r = 0;
    for (c = nc(); !isdigit(c); c = nc());
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r;
}
const int maxn = 4e5 + 100;
int n, a[maxn], b[maxn], id[maxn], maxx, ans;
int L[maxn], Lid[maxn], R[maxn], Rid[maxn];
void mergesort(int k)
{
    int lnum = 0, rnum = 0;
    for (int i = 1; i <= n; ++i)
        if (a[id[i]] & (1 << k)) R[++rnum] = b[i] | (1 << k), Rid[rnum] = id[i];
        else L[++lnum] = b[i], Lid[lnum] = id[i];
    int p1 = 1, p2 = 1, p = 1;
    while (p1 <= lnum && p2 <= rnum)
        if (L[p1] <= R[p2]) b[p] = L[p1], id[p++] = Lid[p1++];
        else b[p] = R[p2], id[p++] = Rid[p2++];
    while (p1 <= lnum) b[p] = L[p1], id[p++] = Lid[p1++];
    while (p2 <= rnum) b[p] = R[p2], id[p++] = Rid[p2++];
}
int count(int ll, int rr)  // count how many in [ll,rr] using two pointer
{
    int bitnum = 0, l = 1, r = n;
    for (int i = n; i; L[i--] = l)
        while (l < i && b[l] + b[i] < ll) ++l;
    for (int i = 1; i <= n; R[i] = std::min(i - 1, r), ++i)
        while (r > 0 && b[i] + b[r] > rr) --r;
    for (int i = 2; i <= n; ++i)
        if (R[i] >= L[i]) bitnum += R[i] - L[i] + 1;
    return bitnum;
}
int main()
{
    read(n);
    for (int i = 1; i <= n; ++i) read(a[i]), maxx = std::max(maxx, a[i]);
    for (int i = 1; i <= n; ++i) id[i] = i;
    for (int k = 0; (1 << k) <= (maxx << 1); ++k)
    {
        mergesort(k);
        int bitnum = count(1 << k, (1 << (k + 1)) - 1) + count((1 << k) + (1 << (k + 1)), (1 << (k + 2)) - 2);
        if (bitnum & 1) ans |= 1 << k;
    }
    printf("%d\n", ans);
    return 0;
}