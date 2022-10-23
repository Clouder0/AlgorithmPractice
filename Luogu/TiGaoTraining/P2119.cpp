#include <cstdio>
#include <algorithm>
#include <ctype.h>
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
const int maxn = 2e5 + 100;
int n, m, a[maxn], num[maxn];
int A[maxn], B[maxn], C[maxn], D[maxn];
int tmp[maxn];
int pairnum[maxn];
signed main()
{
    read(n), read(m);
    int maxx = 0, minn = 200000;
    for (int i = 1; i <= m; ++i) num[read(a[i])]++, maxx = std::max(maxx, a[i]), minn = std::min(minn, a[i]);
    for (int dis = 1;dis < maxx;++dis)
    {
        int up = maxx - dis - 6 * dis - 1;
        if(6 * dis < maxx - dis - up - 1) ++up;
        if(up < 1) break;
        int minb = 1 + 2 * dis;
//        printf("dis:%d up %d minb %d\n",dis,up,minb);
        for (int i = 0; i <= up + 1; ++i) tmp[i] = 0;
        for (int b = up; b >= minb; --b)
        {
            int a = b - 2 * dis;
            if(a < 1) break;
            pairnum[b] = num[b] * num[a];
        }
        for (int i = minb + 1; i <= up; ++i) pairnum[i] += pairnum[i - 1];
        for (int c = maxx - dis;c > 1; --c)
        {
            int d = c + dis;
            if(d < 1) break;
            if(!num[c] || !num[d]) continue;
            int b = c - 6 * dis - 1;
            if(b < 1) break;
            if(6 * dis < c - b - 1) ++b;
            int a = b - 2 * dis;
            if (a < 1) break;
            tmp[b] += num[c] * num[d], C[c] += num[d] * pairnum[b], D[d] += num[c] * pairnum[b];
        }
        for (int i = up - 1; i >= minb; --i) tmp[i] += tmp[i + 1];
        for (int b = up; b >= minb; --b)
        {
            int a = b - 2 * dis;
            if(a < 1) break;
            if(!num[a] || !num[b]) continue;
            A[a] += num[b] * tmp[b], B[b] += num[a] * tmp[b];
        }
    }
    for (int i = 1; i <= m; ++i) printf("%d %d %d %d\n",A[a[i]],B[a[i]],C[a[i]],D[a[i]]);
    return 0;
}