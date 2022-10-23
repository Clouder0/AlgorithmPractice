#include <algorithm>
#include <cstdio>
#include <ctype.h>
using namespace std;
const int mod = 998244353;
const int maxn = 2e6 + 100;
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
T read(T& r)
{
    static char c;
    r = 0;
    for (c = nc(); !isdigit(c); c = nc());
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r;
}
void read(char* s)
{
    static char c;
    for (c = nc(); c != '(' && c != ')'; c = nc());
    for (; c == '(' || c == ')'; c = nc()) *s++ = c;
    *s = '\0';
}
int n, k;
char s[maxn];
inline int add(int x, int y)
{
    int res = x + y;
    return res >= mod ? res - mod : res;
}
inline int mul(int x, int y) { return 1ll * x * y % mod; }
int prod[maxn], prodinv[maxn], inv[maxn], f[maxn];
inline int C(int n, int m) { return mul(prod[n], mul(prodinv[n - m], prodinv[m])); }
void init()
{
    read(n), read(k), read(s + 1);
    prod[0] = prodinv[0] = 1, inv[1] = 1;
    for (int i = 2; i <= n + k; ++i) inv[i] = mul(inv[mod % i], mod - mod / i);
    for (int i = 1; i <= n + k; ++i) prod[i] = mul(prod[i - 1], i), prodinv[i] = mul(prodinv[i - 1], inv[i]);
}
int st[maxn], top, match[maxn];
int rval[maxn], rsum[maxn], d[maxn];
inline int getrange(int l, int r) { return add(rsum[r], mod - rsum[l - 1]); }
int main()
{
    init();
    for (int i = 1; i <= n; ++i)
    {
        if (s[i] == '(') st[++top] = i;
        else
        {
            if (top && s[st[top]] == '(') match[st[top--]] = i;
            else st[++top] = i;
        }
        f[i] = top;
    }
    if (k == 0) { printf("%d\n", f[n]); return 0; }
    for (int i = 1; i <= n; ++i) rval[i] = C(n - i + k - 1, k - 1), rsum[i] = add(rsum[i - 1], rval[i]);
    int sum = 0, res = 0;
    for (int i = 1; i <= n; ++i) sum = add(sum, mul(f[i], rval[i]));
    for (int l = 1; l <= n; ++l)
    {
        d[l] = add(d[l], d[l - 1]);
        f[l] = add(f[l], d[l]);
        int Ltimes = C(l - 1 + k - 1, k - 1);
        res = add(res, mul(Ltimes, sum));
        sum = add(sum, mod - mul(f[l], rval[l]));
        if (s[l] == ')')
        {
            d[l + 1] = add(d[l + 1], mod - 1);
            sum = add(sum, mod - getrange(l + 1, n));
        }
        else
        {
            if (match[l] == 0)
            {
                //no match, all decrease
                d[l + 1] = add(d[l + 1], mod - 1);
                sum = add(sum, mod - getrange(l + 1, n));
            }
            else
            {
                // [l + 1, match[l] - 1] decrease, [match[l], n] increase
                if (match[l] - 1 >= l + 1)
                {
                    d[l + 1] = add(d[l + 1], mod - 1);
                    d[match[l]] = add(d[match[l]], 1);
                    sum = add(sum, mod - getrange(l + 1, match[l] - 1));
                }
                if (match[l] <= n)
                {
                    d[match[l]] = add(d[match[l]], 1);
                    sum = add(sum, getrange(match[l], n));
                }
            }
        }
    }
    printf("%d\n", res);
    return 0;
}