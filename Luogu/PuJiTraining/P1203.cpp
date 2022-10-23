#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 710;
char s[maxn];
int n,lb[maxn], lr[maxn], rb[maxn], rr[maxn];
inline int max(const int &a, const int &b) { return a > b ? a : b; }
int main()
{
    scanf("%d%s", &n, s + 1);
    memcpy(s + n + 1, s + 1, n);
    n <<= 1;
    for (int i = 2; i <= n; ++i)
    {
        if (s[i - 1] == 'w')
            lb[i] = lb[i - 1] + 1, lr[i] = lr[i - 1] + 1;
        else if (s[i - 1] == 'b')
            lb[i] = lb[i - 1] + 1, lr[i] = 0;
        else
            lb[i] = 0, lr[i] = lr[i - 1] + 1;
    }
    for (int i = n - 1; i; --i)
    {
        if (s[i] == 'w')
            rb[i] = rb[i + 1] + 1, rr[i] = rr[i + 1] + 1;
        else if (s[i] == 'b')
            rb[i] = rb[i + 1] + 1, rr[i] = 0;
        else
            rb[i] = 0, rr[i] = rr[i + 1] + 1;
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i)
        ans = max(ans, max(lb[i], lr[i]) + max(rb[i], rr[i]));
    if (ans > n >> 1)
        ans = n >> 1;
    printf("%d\n", ans);
    return 0;
}