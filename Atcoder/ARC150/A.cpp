#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 3e5 + 100;
int T, n, k, sum1[maxn], sumall[maxn];
char s[maxn];
int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &n, &k);
        scanf("%s", s + 1);
        for (int i = 1; i <= n; ++i) sum1[i] = sumall[i] = 0;
        for (int i = 1; i <= n; ++i) sum1[i] = sum1[i-1] + (s[i] == '1'), sumall[i] = sumall[i-1] + (s[i] == '1' || s[i] == '?');
        int res = 0;
        for (int i = k; i <= n; ++i)
            if (sumall[i] - sumall[i - k] == k && sum1[i - k] == 0 && sum1[n] - sum1[i] == 0) 
                ++res;
        puts(res == 1 ? "Yes" : "No");
    }
    return 0;
}