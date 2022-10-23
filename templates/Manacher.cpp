#include <algorithm>
#include <cstdio>
#include <cstring>
const int maxn = 1.5e7 + 100;
char s[maxn];
int n, d1[maxn], d2[maxn];
int main()
{
    scanf("%s", s + 1);
    n = strlen(s + 1);
    int l = 0, r = -1;
    for (int i = 1; i <= n; ++i)
    {
        if (i > r) for (d1[i] = 1; i + d1[i] <= n && i - d1[i] > 0 && s[i + d1[i]] == s[i - d1[i]];) ++d1[i];
        else
        {
            int j = l + r - i;
            if (d1[j] < r - i + 1) d1[i] = d1[j];
            else for (d1[i] = r - i + 1; i + d1[i] <= n && i - d1[i] > 0 && s[i + d1[i]] == s[i - d1[i]];) ++d1[i];
        }
        if (i + d1[i] - 1 > r) l = i - d1[i] + 1, r = i + d1[i] - 1;
    }
    l = 0, r = -1;
    for (int i = 1; i <= n; ++i)
    {
        if (i > r) for (d2[i] = 0; i + d2[i] <= n && i - d2[i] - 1 > 0 && s[i + d2[i]] == s[i - d2[i] - 1];) ++d2[i];
        else
        {
            int j = l + r - i + 1;
            if (d2[j] < r - i + 1) d2[i] = d2[j];
            else for (d2[i] = r - i + 1; i + d2[i] <= n && i - d2[i] - 1 > 0 && s[i + d2[i]] == s[i - d2[i] - 1];) ++d2[i];
        }
        if (i + d2[i] - 1 > r) l = i - d2[i], r = i + d2[i] - 1;
    }
    int maxx = 0;
    for (int i = 1; i <= n; ++i) maxx = std::max(maxx, std::max(2 * d1[i] - 1, 2 * d2[i]));
    printf("%d\n", maxx);
    return 0;
}