#include <cstdio>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
#define int long long
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
int T, n, q, a[maxn], pre[maxn];
long long sum[maxn];
inline long long calc(int l, int r) { return sum[r] - sum[l - 1] - (pre[r] ^ pre[l - 1]); }
int from[maxn], to[maxn];
signed main()
{
    read(T);
    while(T--)
    {
        read(n), read(q);
        for (int i = 1; i <= n; ++i) read(a[i]), pre[i] = pre[i - 1] ^ a[i], sum[i] = sum[i - 1] + a[i];
        for (int i = 1; i <= n; ++i) from[i] = to[i] = i;
        for (int i = n - 1; i; --i)
            if (a[i + 1] == 0 && a[i] == 0) to[i] = to[i + 1];
        for (int i = 2; i <= n; ++i)
            if (a[i] == 0 && a[i - 1] == 0) from[i] = from[i - 1];
        while(q--)
        {
            int L,R;
            read(L), read(R);
            long long res = calc(L, R);
            int resl, resr, reslen = 1 << 30;
            for (int i = 0, l = L; l <= R && i < 40; ++i)
            {
                if (calc(l, R) < res) break;
                int al = l, ar = R, mid, ans = -1;
                while(al <= ar)
                {
                    mid = (al + ar) >> 1;
                    if (calc(l, mid) == res)
                        ar = mid - 1, ans = mid;
                    else
                        al = mid + 1;
                }
                if (ans != -1 && ans - l + 1 < reslen)
                    reslen = ans - l + 1, resl = l, resr = ans;
                l = to[l] + 1;
            }
            for (int i = 0, r = R; r >= L && i < 40; ++i)
            {
                if(calc(L, r) < res) break;
                int al = L, ar = r, mid, ans = -1;
                while(al <= ar)
                {
                    mid = (al + ar) >> 1;
                    if (calc(mid, r) == res)
                        al = mid + 1, ans = mid;
                    else
                        ar = mid - 1;
                }
                if (ans != -1 && r - ans + 1 < reslen)
                    reslen = r - ans + 1, resl = ans, resr = r;
                r = from[r] - 1;
            }

            printf("%lld %lld\n", resl, resr);
        }
    }
    return 0;
}