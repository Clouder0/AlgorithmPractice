#include <cstdio>
#include <queue>
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
const int maxn = 5e5 + 100;
int n;
char s[maxn],t[maxn];
int sum[maxn];
inline int lowbit(int x){return x & -x;}
int ask(int x)
{
    int res = 0;
    for (; x > 0; x -= lowbit(x)) res += sum[x];
    return res;
}
void add(int x, int k) { for (; x <= n; x += lowbit(x)) sum[x] += k; }
queue<int> q[30];
int to[maxn];
int main()
{
    read(n);
    read(s + 1);
    for (int i = 1; i <= n; ++i) s[i] = s[i] - 'a' + 1, q[s[i]].push(i);
    for (int i = 1; i <= n; ++i) t[i] = s[n - i + 1];
    long long ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        to[i] = q[t[i]].front();
        q[t[i]].pop();
        ans += ask(n) - ask(to[i]);
        add(to[i],1);
    }
    printf("%lld\n",ans);
    return 0;
}