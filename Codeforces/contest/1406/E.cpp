#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;
const int maxn = 1e5 + 100;
int n;
int primes[maxn], notprime[maxn], cnt;
void getprime()
{
    notprime[1] = 1;
    for (int i = 2; i <= n; ++i)
    {
        if (!notprime[i]) primes[++cnt] = i;
        for (int j = 1; j <= cnt && primes[j] * i <= n; ++j)
        {
            notprime[i * primes[j]] = 1;
            if ((i % primes[j]) == 0) break;
        }
    }
}
inline int A(const int& x)
{
    cout << "A " << x << endl;
    int res;
    cin >> res;
    return res;
}
inline int B(const int& x)
{
    cout << "B " << x << endl;
    int res;
    cin >> res;
    return res;
}
inline void C(const int& x)
{
    cout << "C " << x << endl;
}
int vis[maxn];
int has[maxn], tot;
int main()
{
    cin >> n;
    if (n == 1)
    {
        C(1);
        return 0;
    }
    getprime();
    int len = sqrt(cnt), num = (cnt + len - 1) / len;
    if (len * len < cnt) ++len;
    int totalnum = n, flag = 0;
    for (int i = 1; i <= num; ++i)
    {
        int L = len * (i - 1) + 1;
        int R = std::min(cnt, len * i);
        for (int j = L; j <= R; ++j)
        {
            int res = B(primes[j]);
            int exp = 0;
            for (int k = primes[j]; k <= n; k += primes[j]) exp += !vis[k], totalnum -= !vis[k], vis[k] = 1;
            if (res != exp) has[++tot] = primes[j];
        }
        if (flag) continue;
        int res = A(1);
        if (res != totalnum)
        {
            flag = 1;
            totalnum = res;
            for (int j = L; j <= R; ++j)
            {
                int t = A(primes[j]);
                int exp2 = 0;
                for (int k = primes[j]; k <= n; k += primes[j]) exp2 += !vis[k];
                if (exp2 != t) has[++tot] = primes[j];
            }
        }
    }
    std::sort(has + 1, has + 1 + tot), tot = std::unique(has + 1, has + 1 + tot) - has - 1;
    int ans = 1;
    for (int i = 1; i <= tot; ++i)
    {
        long long t = 1ll * has[i] * has[i];
        while (t <= n && A(t)) t = t * has[i];
        ans = ans * (t / has[i]);
    }
    C(ans);
    return 0;
}