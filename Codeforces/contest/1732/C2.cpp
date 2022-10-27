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
const int maxn = 2e5 + 100;
int T, n, m, a[maxn], nxt[maxn];
long long sum[maxn], pre[maxn];
inline long long calc(int l, int r) { return sum[r] - sum[l - 1] - (pre[r] ^ pre[l - 1]); }
int main()
{
    read(T);
    while(T--)
    {
        read(n), read(m);
        for (int i = 1; i <= n; ++i) read(a[i]);
        for (int i = 1; i <= n; ++i) pre[i] = pre[i - 1] ^ a[i], sum[i] = sum[i - 1] + a[i];
//        nxt[n + 1] = n + 1;
        nxt[n] = n;
        for (int i = n - 1; i; --i) nxt[i] = (a[i] == 0 && a[i+1] == 0 ? nxt[i + 1] : i);
        while(m--)
        {
            int L, R;
            read(L), read(R);
            long long res = calc(L, R);
            int minn = 1 << 30, resl, resr;
            for (int ll = L, i = 0; ll <= R && i < 50; ll = nxt[ll] + 1, ++i)
            {
                int l = ll, r = R, mid, ans, ansl, ansr;
                while (l <= r)
                {
                    mid = (l + r) >> 1;
                    if (calc(ll, mid) == res)
                        ans = mid, r = mid - 1, ansl = ll, ansr = mid;
                    else
                        l = mid + 1;
                }
                if (ansr - ansl + 1 < minn)
                {
                    minn = ans - ll + 1;
                    resl = ansl, resr = ansr;
                }
            }
            printf("%d %d\n", resl, resr);
        }
    }
    return 0;
}