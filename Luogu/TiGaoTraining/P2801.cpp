#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
template <typename T>
void read(T &r)
{
    static char c;
    r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar());
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar());
}
const int maxn = 1e6 + 100;
int a[maxn];
int L[1100], R[1100], pos[maxn], tag[1100];
vector<int> A[1100];
int n, m;
inline void rebuild(int num)
{
    A[num].clear();
    for (int i = L[num]; i <= R[num]; ++i)
        A[num].push_back(a[i] + tag[num]);
    tag[num] = 0;
    sort(A[num].begin(), A[num].end());
}
inline int search(int num, int c)
{
    c -= tag[num];
    int ll = 0, rr = A[num].size() - 1, mid, ans = -1;
    while (ll <= rr)
    {
        mid = (ll + rr) >> 1;
        if (A[num][mid] < c)
        {
            ans = mid;
            ll = mid + 1;
        }
        else
            rr = mid - 1;
    }
    return A[num].size() - ans - 1;
}
inline int ask(int l, int r, int c)
{
    int p = pos[l], q = pos[r];
    int res = 0;
    if (p == q)
    {
        c -= tag[p];
        for (int i = l; i <= r; ++i)
            res += a[i] >= c;
        return res;
    }
    for (int i = l; i <= R[p]; ++i)
        res += a[i] + tag[p] >= c;
    for (int i = L[q]; i <= r; ++i)
        res += a[i] + tag[q] >= c;
    for (int i = p + 1; i < q; ++i)
        res += search(i, c);
    return res;
}
inline void add(int l, int r, int w)
{
    int p = pos[l], q = pos[r];
    if (p == q)
    {
        for (int i = l; i <= r; ++i)
            a[i] += w;
        rebuild(p);
        return;
    }
    for (int i = l; i <= R[p]; ++i)
        a[i] += w;
    rebuild(p);
    for (int i = L[q]; i <= r; ++i)
        a[i] += w;
    rebuild(q);
    for (int i = p + 1; i < q; ++i)
        tag[i] += w;
}
int main()
{
    read(n);
    read(m);
    int blockSize = sqrt(n);
    int blockNum = n / blockSize;
    if (blockSize * blockNum < n)
        ++blockNum;
    for (int i = 1; i < blockNum; ++i)
    {
        L[i] = R[i - 1] + 1;
        R[i] = L[i] + blockSize - 1;
        for (int k = L[i]; k <= R[i]; ++k)
            read(a[k]), pos[k] = i, A[i].push_back(a[k]);
    }
    L[blockNum] = R[blockNum - 1] + 1;
    R[blockNum] = n;
    for (int k = L[blockNum]; k <= R[blockNum]; ++k)
        read(a[k]), pos[k] = blockNum, A[blockNum].push_back(a[k]);
    for (int i = 1; i <= blockNum; ++i)
        sort(A[i].begin(), A[i].end());
    char opt[10];
    int a, b, c;
    for (int i = 1; i <= m; ++i)
    {
        scanf("%s", opt);
        read(a);
        read(b);
        read(c);
        if (opt[0] == 'M')
            add(a, b, c);
        else
            printf("%d\n", ask(a, b, c));
    }
    return 0;
}