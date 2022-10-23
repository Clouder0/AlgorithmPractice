#include <cstdio>
#include <cstring>
using namespace std;
template <typename T>
void read(T &r)
{
    static char c;
    static int flag;
    flag = 1, r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar()) if (c == '-') flag = -1;
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar());
    r *= flag;
}
const int maxn = 6000;
int n, w, s;
long long dp[2][maxn];
long long a[maxn];
int head, tail, q1, q2, q[maxn];
int main()
{
    read(n);
    read(w);
    read(s);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    int now = 0, last = 1;
    for (int i = 1; i <= n; ++i)
    {
        memset(dp[now], ~0x3f, sizeof(dp[now]));
        head = 1, tail = 0;
        q1 = q2 = 1;
        for (int j = 1; j <= i && j <= w; ++j)
        {
            while (q2 <= j + s - 1 && q2 <= w && q2 < i)
            {
                while (tail >= head && dp[last][q[tail]] <= dp[last][q2]) --tail;
                q[++tail] = q2;
                ++q2;
            }
            while (tail >= head && q[head] < j - 1) ++head;
            dp[now][j] = dp[last][q[head]] + a[i] * j;
        }
        now ^= 1;
        last ^= 1;
    }
    long long ans = -(1ll << 60);
    for (int i = 1; i <= w; ++i)
        ans = ans > dp[last][i] ? ans : dp[last][i];
    printf("%lld", ans);
    return 0;
}