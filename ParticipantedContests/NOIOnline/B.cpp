#include <cstdio>
using namespace std;
template<typename T>
inline void swap(T &a,T &b)
{
	T t = a;
	a = b;
	b = t;
}
template <typename T>
inline T read(T &r)
{
    static char c;
    r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar());
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar());
    return r;
}
const int maxn = 1e5 + 100;
int n, m;
long long num;
int a[maxn];
int b[maxn];
inline int lowbit(const int &x)
{
    return x & (-x);
}
inline int ask(int p)
{
    int res = 0;
    while (p)
    {
        res += b[p];
        p -= lowbit(p);
    }
    return res;
}
inline void add(int p, int x)
{
    while (p <= n)
    {
        b[p] += x;
        p += lowbit(p);
    }
}
int main()
{
    freopen("bubble.in","r",stdin);
    freopen("bubble.out","w",stdout);
    read(n);
    read(m);
    for (int i = 1; i <= n; ++i)
    {
        read(a[i]);
        num += ask(n) - ask(a[i]);
        add(a[i], 1);
    }
    int t;
    long long c;
    for (int i = 1; i <= m; ++i)
    {
        read(t);
        read(c);
        if (t == 1)
        {
            if (a[c] < a[c + 1])
                ++num;
            else
                --num;
            swap(a[c],a[c+1]);
        }
        else
        {
            if (c > num)
                puts("0");
            else
                printf("%d\n", num - c);
        }
    }
    return 0;
}
