#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
int a[100005], x[100005], y[100005];
int main()
{
    int T = 1, kase = 0;
    cin >> T;
    while (T--)
    {
        int n, k;
        scanf("%d%d", &n, &k);
        for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
        map<int, int> mp;
        mp[-1] = 0;
        for (int i = 1; i <= k; i++) scanf("%d%d", &x[i], &y[i]), mp[x[i]] = y[i];
        long long sum = 0;
        for (int i = 1; i <= n; i++) sum += a[i];
        sort(a + 1, a + n + 1);
        int cnt = 0, x = 0;
        mp[1e9 + 1] = 0;
        vector<pair<int, int>> v;
        for (auto t : mp)
        {
            if (t.second == 0 && t.first != -1)
            {
                while (x < n && a[x + 1] < t.first) x++, cnt++;
                for (auto temp : v)
                {
                    if (cnt == 0) break;
                    if (cnt <= temp.second)
                        sum -= 1LL * temp.first * cnt, cnt = 0;
                    else
                        sum -= 1LL * temp.first * temp.second, cnt -= temp.second;
                }
                v.clear();
            }
            v.push_back(t);
            if (!mp.count(t.first + 1)) v.push_back({t.first + 1, 1e9});
        }
        puts(sum % 2 ? "Pico" : "FuuFuu");
    }
    return 0;
}