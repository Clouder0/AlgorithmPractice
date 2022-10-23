#include <cstdio>
#include <cstring>
#define int long long
template <typename T>
inline void _swap(T &a, T &b)
{
    T t = a;
    a = b;
    b = t;
}
template <typename T>
void read(T &r)
{
    static char c;
    r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar());
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar());
}
const int maxn = 2e5 + 10;
int n, m;
int a[maxn];
long long tree[maxn];
inline int lowbit(const int &x)
{
    return x & (-x);
}
inline long long ask(int x)
{
    long long ans = 0;
    for (; x; x -= lowbit(x))
        ans += tree[x];
    return ans;
}
inline void add(int x, const long long &k)
{
    for (; x <= n; x += lowbit(x))
        tree[x] += k;
}
long long before[maxn], record[maxn];
signed main()
{
    read(n);
    read(m);
    int tot = 0;
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        add(a[i], 1);
        before[i] = i - ask(a[i]);
        tot += before[i];
        record[before[i]]++;
    }
    memset(tree, 0, sizeof(tree));
    add(1, tot);
    tot = 0;
    for (int i = 0; i < n; ++i)
    {
        tot += record[i];
        add(i + 2, tot - n);
    }
    long long t, c;
    while (m--)
    {
        read(t);
        read(c);
        if (c > n - 1)
            c = n - 1;
        if (t == 1)
        {
            if (a[c] < a[c + 1])
            {
                _swap(a[c], a[c + 1]);
                _swap(before[c], before[c + 1]);
                add(1, 1);
                add(before[c + 1] + 2, -1);
                ++before[c + 1];
            }
            else
            {
                _swap(a[c], a[c + 1]);
                _swap(before[c], before[c + 1]);
                add(1, -1);
                before[c]--;
                add(before[c] + 2, 1);
            }
        }
        else
        {
            printf("%lld\n", ask(c + 1));
        }
    }
    return 0;
}