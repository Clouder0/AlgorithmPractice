#include <algorithm>
#include <bitset>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#define MAXN 50016
#define LL long long
using namespace std;
int n;
char a[MAXN], b[MAXN];
int sum[MAXN];
int minn, maxx;
bitset<MAXN> S[MAXN], ans, L, map1, map0;
void init()
{
    map1 = map0 = ans = L = bitset<MAXN>();
    for (int i = 0; i <= maxx - minn; i++) S[i] = bitset<MAXN>();
    minn = maxx = 0;
    for (int i = 1; i <= n; i++) sum[i] = 0;
}
int main()
{
    // freopen("input.txt","r",stdin);
    int t;
    scanf("%d", &t);
    while (t--)
    {
        init();

        ans = ~ans;
        scanf("%d", &n);
        scanf("%s", a + 1);
        scanf("%s", b + 1);

        for (int i = 1; i <= n; i++)
        {
            sum[i] = sum[i - 1] + ((a[i] - '0') ? 1 : -1);
            minn = min(minn, sum[i]);
            maxx = max(maxx, sum[i]);
        }

        bitset<MAXN>* T = S - minn;

        T[0][n] = 1;
        map1 = ~map1;  // all 1 ,map1 all 0

        for (int i = 1, presum = 0; i <= n; i++)
        {
            map0[i] = 1;
            map1[i] = 0;

            if (a[i] == '0')
                L ^= T[--presum];
            else
                L ^= T[presum++];
            T[presum][n - i] = 1;
            int hi = L[n];
            if (hi)
                ans &= (b[i] == '1' ? (L >> (n - i)) | map1 : ~((L >> (n - i)) | map1));
            else
                ans &= (b[i] == '1' ? (L >> (n - i)) & map0 : ~((L >> (n - i)) & map0));
        }
        for (int i = 1; i <= n; i++) printf("%d", ans[i] ? 1 : 0);
        putchar('\n');
    }
    return 0;
}
