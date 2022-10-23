#include <algorithm>
#include <cstdio>
#include <ctype.h>
#include <set>
using namespace std;
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
    for (c = nc(); !isdigit(c); c = nc()) if (c == '-') flag = -1;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r *= flag;
}
const int maxn = 2e5 + 100;
int n, a[maxn], hb[maxn];
set<pair<int, int> > S;
int main()
{
    read(n);
    for (int i = 1; i <= n; ++i) read(a[i]);
    for (int i = 1; i <= n; ++i)
        for (int j = 29; j >= 0; --j)
            if (a[i] & (1 << j)) { hb[i] = j; break; }
    for (int l = 1; l <= n; ++l)
    {
        int maxx = 1 << (hb[l] + 1);
        long long now = a[l + 1];
        for (int r = l + 2; r <= n; ++r)
        {
            if (now >= maxx) break;
            if ((a[l] ^ a[r]) == now) S.insert(make_pair(l, r));
            now += a[r];
        }
    }
    for (int r = n; r > 0; --r)
    {
        int maxx = 1 << (hb[r] + 1);
        long long now = a[r - 1];
        for (int l = r - 2; l > 0; --l)
        {
            if (now >= maxx) break;
            if ((a[l] ^ a[r]) == now) S.insert(make_pair(l, r));
            now += a[l];
        }
    }
    printf("%d\n", S.size());
    return 0;
}