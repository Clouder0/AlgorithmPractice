#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#include <ctype.h>
using namespace std;
const int bufSize = 1e6;
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
const int maxn = 110;
int n,W;
int wsum[maxn];
int f[33][1100];
vector<int> value[33],weight[33];
inline void init()
{
    memset(wsum, 0, sizeof(wsum)), memset(f, 0, sizeof(f));
    for (int i = 0; i <= 31; ++i) value[i].clear(), weight[i].clear();
}
int main()
{
    while(1)
    {
        read(n), read(W);
        if (n == -1 || W == -1) return 0;
        init();
        int len = 0;
        for (int i = 1, w, v, t; i <= n; ++i)
        {
            read(w), read(v);
            for (t = 0; !(w & 1); w >>= 1) ++t;
            len = max(len, t), wsum[t] += w, value[t].push_back(v), weight[t].push_back(w);
        }
        for (int i = 0; i <= len; ++i)
            for (unsigned int j = 0; j < value[i].size(); ++j)
                for (int k = wsum[i]; k >= weight[i][j]; --k)
                    f[i][k] = max(f[i][k],f[i][k - weight[i][j]] + value[i][j]);
        while(W >> len) ++len;
        --len;
        for (int i = 1; i <= len; ++i)
        {
            wsum[i] += (wsum[i - 1] + 1) / 2;
            for (int j = wsum[i]; j >= 0; --j)
                for (int k = 0; k <= j; ++k) 
                    f[i][j] = max(f[i][j], f[i][j - k] + f[i - 1][min(wsum[i - 1], (k << 1) | ((W >> (i - 1)) & 1))]);
        }
        printf("%d\n",f[len][1]);
    }
    return 0;
}