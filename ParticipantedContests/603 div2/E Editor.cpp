#include <cstdio>
using namespace std;
int n, pos = 1;
const int maxn = 1000010;
int sum[maxn << 2], smax[maxn << 2], smin[maxn << 2];
inline int max(const int &a, const int &b) { return a > b ? a : b; }
inline int min(const int &a, const int &b) { return a < b ? a : b; }
void push_up(const int &p)
{
    sum[p] = sum[p << 1] + sum[p << 1 | 1];
    smax[p] = max(smax[p << 1], sum[p << 1] + smax[p << 1 | 1]);
    smin[p] = min(smin[p << 1], sum[p << 1] + smin[p << 1 | 1]);
}
int k;
void update(const int &l, const int &r, const int &p)
{
    if (l == r)
    {
        //单点修改
        sum[p] = smax[p] = smin[p] = k;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid)
        update(l, mid, p << 1);
    else
        update(mid + 1, r, p << 1 | 1);
    push_up(p);
}
int main()
{
    scanf("%d", &n);
    getchar();
    char c;
    for (int i = 1; i <= n; ++i)
    {
        c = getchar();
        switch (c)
        {
        case 'L':
            pos = (pos == 1 ? pos : pos - 1);
            break;
        case 'R':
            ++pos;
            break;
        case '(':
            k = 1;
            update(1, n, 1);
            break;
        case ')':
            k = -1;
            update(1, n, 1);
            break;
        default:
            k = 0;
            update(1, n, 1); //修改成非括号字母也要修改权值
        }
        //当前序列合法条件： 权值和为0，最小权值和>=0
        if (sum[1] != 0 || smin[1] < 0)
        {
            printf("-1 ");
            continue;
        }
        printf("%d ", smax[1]);
    }
    return 0;
}