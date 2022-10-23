#include <cstdio>
#include <cstring>
#include <algorithm>
using std::max;
const int maxn = 1e6 + 100;
char s[maxn];
int n, d1[maxn], d2[maxn], maxx[maxn];
void modify(int x, int k) { for (; x <= n; x += x & -x) maxx[x] = max(maxx[x], k); }
int ask(int x) { int res = 0; for (; x; x -= x & -x) res = max(res, maxx[x]); return res; }
int main()
{
    scanf("%s", s + 1);
    n = strlen(s + 1);
    int l = 1, r = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (i <= r) d1[i] = std::min(d1[l + r - i], r - i + 1);
        for (; i + d1[i] <= n && i - d1[i] > 0 && s[i + d1[i]] == s[i - d1[i]];) ++d1[i];
        if (i + d1[i] - 1 > r) r = i + d1[i] - 1, l = i - d1[i] + 1;
    }
    l = 1, r = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (i <= r) d2[i] = std::min(r - i, d2[l + r - i - 1]);
        for (; i + d2[i] + 1 <= n && i - d2[i] > 0 && s[i + d2[i] + 1] == s[i - d2[i]];) ++d2[i];
        if (i + d2[i] > r) r = i + d2[i], l = i - d2[i] + 1;
    }
    int res = 0;
    for (int i = n; i; --i)
    {
        l = i - d1[i] + 1, r = i + d1[i] - 1;
        res = max(res, r - l + 1 - 2 * r + ask(std::min(n, r + 1)) - 2);
        if(d2[i])
        {
            l = i - d2[i] + 1, r = i + d2[i];
            res = max(res, r - l + 1 - 2 * r + ask(std::min(n, r + 1)) - 2);
            modify(l,r - l + 1 + 2 * l);
        }
        l = i - d1[i] + 1, r = i + d1[i] - 1;
        modify(l, r - l + 1 + 2 * l);
    }
    printf("%d\n", res);
    return 0;
}