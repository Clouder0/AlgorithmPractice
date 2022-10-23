#include <cstdio>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
inline char nc(){static char buf[bufSize], *p1 = buf, *p2 = buf;return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;}
template<typename T> inline T read(T &r){static char c;r = 0;for (c = nc(); !isdigit(c); c = nc());for (; isdigit(c); c = nc()) r = r * 10 + c - 48;return r;}
const int maxn = 1e5 + 100;
int N, K, cnt;
inline bool check(int n, int k)
{
    if (n % 2 == 0) return false;
    if (k == 0) return ((n & (n + 1)) == 0);
    if (k == 1) return (n & (n + 1));
    if (n == 9 && k == 2) return false;
    return k > 0 && k * 2 + 3 <= n;
}
void dfs(int n, int k, int fa)
{
    printf("%d ", fa);
    int now = ++cnt;
    if (n == 1) return;
    for (int l = 1; l < n; l = l * 2 + 1)
    {
        int r = n - l - 1;
        int more = k - (std::max(l, r) >= std::min(l, r) * 2);
        if(check(l,0) && check(r,more)) {dfs(l, 0, now), dfs(r, more, now);return;}
    }
}
int main()
{
    read(N), read(K);
    if (!check(N, K)) puts("NO"); else puts("YES"), dfs(N, K, 0);
    return 0;
}