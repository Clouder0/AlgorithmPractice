#include <cstdio>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
#define DEBUG
using std::min;
using std::max;
#define int long long
inline char nc()
{
    #ifdef DEBUG
    return getchar();
    #endif
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
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
int A, B, C, D;
signed main()
{
    read(A), read(B), read(C), read(D);
    long long res = 0;
    for (int x = A; x <= B; ++x)
    {
        int mid = min(D - x + 1, C);
        if (mid >= B)
        {
            int num = mid - B + 1;
            int left = x + B - 1, right = x + mid - 1;
            left = max(left, C);
            if (right >= left) num = right - left + 1, res += (left + right) * num / 2 - num * (C - 1);
        }
        mid = max(B,D - x + 2);
        if(mid <= C)
        {
            int num = C - mid + 1;
            res += num * (D - C + 1);
        }
    }
    printf("%lld\n", res);
    return 0;
}