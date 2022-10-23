#include <cstdio>
#include <algorithm>
#include <ctype.h>
#define int long long
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
const long long mod = 998244353;
long long n, m, q, a, b, c, d;
long long mul(long long a, long long b) { return ((a % mod) * (b % mod)) % mod; }
long long add(long long a, long long b) { return (a + b + mod) % mod; }
const long long inv = 499122177;
signed main()
{
    read(n),read(m);
    read(q);
    while(q--)
    {
        read(a), read(b), read(c), read(d);
        std::swap(b, c);
        int col_even = (d - b + 1) / 2, col_odd = d - b + 1 - col_even;
        if ((b & 1) == 0) std::swap(col_even, col_odd);
        int odd_row_has = col_odd;
        int even_row_has = col_even;
        int odd_start = (b & 1) ? b : b + 1;
        int odd_end = (d & 1) ? d : d - 1;
        int even_start = (b & 1) ? b + 1 : b;
        int even_end = (d & 1) ? d - 1 : d;

        int even_row_num = (c - a + 1) / 2, odd_row_num = c - a + 1 - even_row_num;
        if ((a & 1) == 0) std::swap(even_row_num, odd_row_num);
        int even_row_start = (a & 1) ? a + 1 : a;
        int odd_row_start = (a & 1) ? a : a + 1;
        int even_row_end = (c & 1) ? c - 1 : c;
        int odd_row_end = (c & 1) ? c : c - 1;

        int suf_odd_row_sum = mul(odd_row_num, mul(inv, mul(add(odd_start, odd_end), odd_row_has)));
        int suf_even_row_sum = mul(even_row_num, mul(inv, mul(add(even_start, even_end), even_row_has)));
        int pre_odd_row_sum = mul(m, mul(odd_row_num, mul(inv, mul(odd_row_has, add(odd_row_start - 1, odd_row_end - 1)))));
        int pre_even_row_sum = mul(m, mul(even_row_num, mul(inv, mul(even_row_has, add(even_row_start - 1, even_row_end - 1)))));
        printf("%lld\n", add(pre_even_row_sum, add(pre_odd_row_sum, add(suf_even_row_sum, suf_odd_row_sum))));
    }
    return 0;
}