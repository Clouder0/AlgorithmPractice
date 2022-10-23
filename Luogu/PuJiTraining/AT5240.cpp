#include <cstdio>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
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
const int maxn = 1e6 + 100;
int X, Y, A, B, C;
int p[maxn], q[maxn], a[maxn],cnt;
int main()
{
    read(X),read(Y),read(A),read(B),read(C); 
    for (int i = 1; i <= A; ++i) read(p[i]);
    for (int i = 1; i <= B; ++i) read(q[i]);
    for (int i = 1; i <= C; ++i) read(a[++cnt]);
    std::sort(p + 1, p + 1 + A), std::sort(q + 1, q + 1 + B);
    for (int i = 1; i <= X; ++i) a[++cnt] = p[A - i + 1];
    for (int i = 1; i <= Y; ++i) a[++cnt] = q[B - i + 1];
    std::sort(a + 1,a + 1 + cnt);
    long long res = 0;
    for (int i = 1; i <= X + Y; ++i) res += a[cnt - i + 1];
    printf("%lld\n", res);
    return 0;
}