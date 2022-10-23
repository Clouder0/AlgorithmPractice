#include <algorithm>
#include <cstdio>
#include <ctype.h>

using namespace std;
const int bufSize = 1e6;
#define DEBUG
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
const int maxn = 1e5 + 100;
int T, n;
char A[maxn], B[maxn];
int cnt[30][30];
int main()
{
    read(T);
    while (T--)
    {
        read(n);
        read(A + 1), read(B + 1);
        int times = 0;
        for (int i = 1; i <= n; ++i) if (A[i] > B[i]) goto fail;
        for (int i = 1; i <= 20; ++i) for (int j = 1; j <= 20; ++j) cnt[i][j] = 0;
        for (int i = 1; i <= n; ++i) if (A[i] != B[i]) cnt[A[i] - 'a' + 1][B[i] - 'a' + 1]++;
        for (int i = 1; i <= 20; ++i)
        {
            for (int j = i + 1; j <= 20; ++j)
            {
                if (!cnt[i][j]) continue;
                ++times;
                for (int k = j + 1; k <= 20; ++k) cnt[j][k] += cnt[i][k], cnt[i][k] = 0;
            }
        }
        printf("%d\n", times);
        continue;
    fail:
        puts("-1");
    }
    return 0;
}