#include <algorithm>
#include <cstdio>
using namespace std;
const int maxn = 1e5 + 100;
int T, n;
struct node
{
    int val, id;
} A[maxn];
bool cmp(const node& a, const node& b)
{
    return a.val == b.val ? a.id < b.id : a.val < b.val;
}
int mv[maxn], onenum, last;
int s[maxn], top;
int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i)
            scanf("%d", &A[i].val), A[i].id = i;
        sort(A + 1, A + 1 + n, cmp);
        for (int i = 1; i <= n; ++i)
            mv[i] = (abs(A[i].id - i) & 1);
        for (int l = 1, r; l <= n; ++l)
        {
            r = l - 1;
            onenum = 0;
            while (r + 1 <= n && A[r + 1].val == A[l].val)
                ++r, onenum += mv[r];
            if (onenum & 1)
                goto end;
            top = 0;
            for (int i = l; i <= r; ++i)
            {
                if (mv[i])
                {
                    if (top && ((i - s[top] - 1) & 1) == 0)
                    {
                        --top;
                    }
                    else
                        s[++top] = i;
                }
            }
            if (top) goto end;
            l = r;
        }
        puts("YES");
        continue;
    end:
        puts("NO");
    }
    return 0;
}