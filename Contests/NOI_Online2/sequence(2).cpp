#include <cstdio>
#include <map>
template <typename T>
void read(T &r)
{
    static char c;
    r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar());
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar());
}
const int maxn = 1e5;
const int mod = 1e9 + 7;
int n;
int a[maxn];
std::map<int,int> last;
int record[maxn], sum[maxn], next[maxn];
long long ans;
int main()
{
    freopen("sequence.in", "r", stdin);
    freopen("sequence2.out","w",stdout);
    read(n);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    for (int i = 1; i <= n; ++i)
    {
        int siz = last.size();
        int t = last[a[i]];
        if(t == 0)
            ++siz;
        sum[i] = siz;
        ans = (ans + sum[i] * sum[i]) % mod;
        if(t)
            next[t] = i;
        last[a[i]] = i;
    }
    for (int i = 1; i < n; ++i)
    {
        //弹出I
        if (next[i])
        {
            for (int j = i + 1; j < next[i]; ++j)
            {
                sum[j]--;
            }
            for (int j = i + 1; j <= n; ++j)
                ans = (ans + sum[j] * sum[j]) % mod;
        }
        else
        {
            for (int j = i + 1; j <= n; ++j)
                sum[j]--;
            for (int j = i + 1; j <= n; ++j)
                ans = (ans + sum[j] * sum[j]) % mod;
        }
    }
    printf("%lld", ans);
    return 0;
}
