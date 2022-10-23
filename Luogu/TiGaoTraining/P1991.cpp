#include <cstdio>
#include <cmath>
#include <algorithm>
template <typename T>
void read(T &r)
{
    static char c;
    for (c = getchar(); c > '9' || c < '0'; c = getchar());
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar());
}
const int maxp = 510;
int s, p;
int X[maxp], Y[maxp];
double dis[maxp][maxp];
double D[maxp * maxp];
int tot;
int fa[maxp];
int find(const int &x)
{
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}
inline void unite(const int &a, const int &b)
{
    int x = find(a), y = find(b);
    if (x == y)
        return;
    fa[x] = y;
}
inline bool check(double d)
{
    for (int i = 1; i <= p; ++i)
        fa[i] = i;
    for (int i = 1; i <= p; ++i)
        for (int j = i + 1; j <= p; ++j)
            if (dis[i][j] <= d)
                unite(i, j);
    int num = 0;
    for (int i = 1; i <= p; ++i)
        if (find(i) == i)
            ++num;
    if (num == 1)
        return true;
    return tree <= s;
}
int main()
{
    read(s);
    read(p);
    for (int i = 1; i <= p; ++i)
        read(X[i]), read(Y[i]);
    for (int i = 1; i <= p; ++i)
        for (int j = i + 1; j <= p; ++j)
            dis[i][j] = dis[j][i] = std::sqrt((X[i] - X[j]) * (X[i] - X[j]) + (Y[i] - Y[j]) * (Y[i] - Y[j])), D[++tot] = dis[i][j];
    std::sort(D + 1, D + 1 + tot);
    tot = std::unique(D + 1, D + 1 + tot) - D;
    int l = 1, r = tot, mid, ans;
    while (l <= r)
    {
        mid = l + r >> 1;
        if (check(D[mid]))
            ans = mid, r = mid - 1;
        else
            l = mid + 1;
    }
    printf("%.2f", D[ans]);
    return 0;
}