#include <algorithm>
#include <cstdio>
#include <ctype.h>
const int bufSize = 1e6;
using namespace std;
inline char nc()
{
#ifdef DEBUG
    return getchar();
#endif
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
inline void read(char* s)
{
    static char c;
    for (; !isalpha(c); c = nc());
    for (; isalpha(c); c = nc()) *s++ = c;
    *s = '\0';
}
template <typename T>
inline T read(T& r)
{
    static char c;
    static int flag;
    flag = 1, r = 0;
    for (c = nc(); !isdigit(c); c = nc()) if (c == '-') flag = -1;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r *= flag;
}
const int maxn = 5e6 + 100;
int n;
int type[maxn], price[maxn], t[maxn];
bool used[maxn];
int q[maxn], qh, qt;
int main()
{
    read(n);
    qh = 1, qt = 0;
    for (int i = 1; i <= n; ++i) read(type[i]), read(price[i]), read(t[i]);
    long long ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        while (qt >= qh && t[i] - t[q[qh]] > 45) ++qh;
        if (type[i] == 1)
        {
            for (int j = qh; j <= qt; ++j)
                if (!used[q[j]] && price[q[j]] >= price[i])
                {
                    used[q[j]] = 1;
                    goto end;
                }
            ans += price[i];
        }
        else
        {
            ans += price[i];
            q[++qt] = i;
        }
    end:;
    }
    printf("%lld\n", ans);
    return 0;
}