#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
const int maxn = 2e5 + 100;
struct A
{
    string s;
    int num, X;
}a[maxn];
bool cmp(const A& a, const A& b)
{
    return 1ll * a.num * b.X < 1ll * b.num * a.X;
}
int n;
string S;
signed main()
{
    cin >> n;
    for (int i = 1; i <= n; ++i) 
    {
        cin >> a[i].s;
        for (string::iterator it = a[i].s.begin(); it != a[i].s.end(); ++it)
            if (*it != 'X') a[i].num += *it - '0';
            else a[i].X++;
    }
    sort(a + 1, a + 1 + n, cmp);
    for (int i = 1; i <= n; ++i) S = S + a[i].s;
    int pre = 0;
    long long res = 0;
    for(string::iterator it = S.begin();it!=S.end();++it)
    {
        if(*it == 'X') ++pre;
        else res += 1ll * pre * (*it - '0');
    }
    cout << res << endl;
    return 0;
}