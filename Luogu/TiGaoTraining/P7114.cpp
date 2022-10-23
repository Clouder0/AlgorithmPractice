#include <algorithm>
#include <cstdio>
#include <cstring>
const int bufSize = 1e6;
const int maxn = 2e6 + 100;
int T, n, z[maxn], pre[maxn], suf[maxn], tmp[30];
char s[maxn];
int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%s", s + 1), n = strlen(s + 1);
        int l = 1, r = 0;
        for (int i = 2; i <= n; ++i)
        {
            z[i] = 0;
            if (i > r) for (; i + z[i] <= n && s[z[i] + 1] == s[i + z[i]];) ++z[i];
            else
            {
                z[i] = std::min(r - i + 1, z[i - l + 1]);
                for (; i + z[i] <= n && s[z[i] + 1] == s[i + z[i]];) ++z[i];
            }
            if (i + z[i] - 1 > r) r = i + z[i] - 1, l = i;
        }
        for (int i = 1; i <= n; ++i)
        {
            if (tmp[s[i] - 'a']) pre[i] = pre[i - 1] - 1; else pre[i] = pre[i - 1] + 1;
            tmp[s[i] - 'a'] ^= 1;
        }
        for (int i = 0; i <= 26; ++i) tmp[i] = 0;
        suf[n + 1] = 0;
        for (int i = n; i; --i)
        {
            if (tmp[s[i] - 'a']) suf[i] = suf[i + 1] - 1;
            else suf[i] = suf[i + 1] + 1;
            tmp[s[i] - 'a'] ^= 1;
        }
        for (int i = 0; i <= 26; ++i) tmp[i] = 0;
        long long res = 0;
        for (int len = 2; len < n; ++len)
        {
            for (int i = pre[len - 1]; i <= 26; ++i) ++tmp[i];
            res += tmp[suf[len + 1]];
            for (int l = 2 * len + 1; z[l - len] >= len && l <= n; l += len) res += tmp[suf[l]];
        }
        printf("%lld\n", res);
        for (int i = 0; i <= 26; ++i) tmp[i] = 0;
    }
    return 0;
}