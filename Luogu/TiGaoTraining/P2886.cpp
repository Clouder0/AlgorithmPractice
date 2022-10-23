#include <cstdio>
#include <cstring>
#include <map>
template <typename T>
inline T min(const T &a, const T &b) { return a < b ? a : b; }
template <typename T>
void read(T &r)
{
    static char c;
    r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar());
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar());
}
std::map<int, int> mp;
int tot;
int m, num, s, t;
int dis[210][210];
int A[210][210], B[210][210], C[210][210];
int main()
{
    read(num);
    read(m);
    read(s);
    read(t);
    for (int i = 1; i <= m; ++i)
    {
        int u, v, len;
        read(len);
        read(u);
        read(v);
        std::map<int, int>::iterator it = mp.find(u);
        if (it == mp.end())
            mp[u] = ++tot, u = tot;
        else
            u = it->second;
        it = mp.find(v);
        if (it == mp.end())
            mp[v] = ++tot, v = tot;
        else
            v = it->second;
        dis[u][v] = dis[v][u] = len;
    }
    for (int i = 1; i <= tot; ++i)
        for (int j = 1; j <= tot; ++j)
            A[i][j] = B[i][j] = (dis[i][j] > 0 ? dis[i][j] : 1 << 28);
    s = mp[s], t = mp[t];
    --num;
    while (num)
    {
        if (num & 1)
        {
            for (int i = 1; i <= tot; ++i)
                for (int j = 1; j <= tot; ++j)
                    C[i][j] = 1 << 30;
            for (int i = 1; i <= tot; ++i)
                for (int j = 1; j <= tot; ++j)
                    for (int k = 1; k <= tot; ++k)
                        C[i][k] = min(C[i][k], A[i][j] + B[j][k]);
            for (int i = 1; i <= tot; ++i)
                for (int j = 1; j <= tot; ++j)
                    A[i][j] = C[i][j];
        }
        for (int i = 1; i <= tot; ++i)
            for (int j = 1; j <= tot; ++j)
                C[i][j] = 1 << 30;
        for (int i = 1; i <= tot; ++i)
            for (int j = 1; j <= tot; ++j)
                for (int k = 1; k <= tot; ++k)
                    C[i][k] = min(C[i][k], B[i][j] + B[j][k]);
        for (int i = 1; i <= tot; ++i)
            for (int j = 1; j <= tot; ++j)
                B[i][j] = C[i][j];
        num >>= 1;
    }
    printf("%d", A[s][t]);
    return 0;
}