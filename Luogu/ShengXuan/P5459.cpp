#include <cstdio>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
using namespace std;
#define DEBUG
inline char nc()
{
    #ifdef DEBUG
    return getchar();
    #endif
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
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
const int maxn = 3e5 + 100;
int n, L, R, a[maxn], b[maxn], cnt;
long long sum[maxn], H[maxn];
inline int lowbit(int x){return x & -x;}
void add(int x,int k)
{
    for (; x <= cnt; x += lowbit(x)) b[x] += k;
}
int ask(int x)
{
    int res = 0;
    for (; x > 0; x -= lowbit(x)) res += b[x];
    return res;
}
int main()
{
    read(n), read(L), read(R);
    for (int i = 1; i <= n; ++i) read(a[i]), sum[i] = sum[i - 1] + a[i];
    for (int i = 1; i <= n; ++i) H[++cnt] = sum[i];
    for (int i = 1; i <= n; ++i) H[++cnt] = L + sum[i - 1] - 1, H[++cnt] = R + sum[i - 1];
    sort(H + 1, H + 1 + cnt), cnt = unique(H + 1, H + 1 + cnt) - H - 1;
    long long res = 0;
    for (int l = n; l; --l)
    {
        add(lower_bound(H + 1, H + 1 + cnt, sum[l]) - H, 1);
        res += ask(lower_bound(H + 1, H + 1 + cnt, sum[l - 1] + R) - H) - ask(lower_bound(H + 1, H + 1 + cnt, sum[l - 1] + L - 1) - H);
    }
    printf("%lld\n",res);
    return 0;
}