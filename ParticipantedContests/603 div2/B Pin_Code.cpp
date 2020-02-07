#include <cstdio>
#include <iostream>
#include <string>
#include <map>
using namespace std;
int t, n, ans;
map<string, int> ht;
string all[11];
int main()
{
    cin.tie(0);
    ios::sync_with_stdio(false);
    cin >> t;
    while (t--)
    {
        ans = 0;
        ht.clear();
        cin >> n;
        for (int i = 1; i <= n; ++i)
            cin >> all[i], ++ht[all[i]];
        for (map<string, int>::iterator it = ht.begin(); it != ht.end(); ++it)
            ans += it->second - 1;
        cout << ans << endl;//直接先统计出答案，每组都要且只要进行n-1次变换
        for (int i = 1; i <= n; ++i)
        {
            map<string, int>::iterator it = ht.find(all[i]);
            if (it == ht.end())
                continue;
            if (it->second > 1)
            {
                string s = all[i];
                for (int j = 0; j <= 9; ++j)
                {
                    s[3] = j + '0';
                    if (ht.find(s) == ht.end())
                    {
                        ht[s] = 1;
                        cout << s << endl;
                        --it->second;//这里只进行1次变换，因为每个输入的数据都会遍历到，所以最后一定会减到1
                        break;
                    }
                }
            }
            else
                cout << all[i] << endl;
        }
    }
    return 0;
}