#include <cstdio>
#include <iostream>
#include <string>
#include <map>
using namespace std;
int n;
string all[15];
map<string,int> getmoney;
map<string,int> money;
int main()
{
    cin.tie(0);
    ios::sync_with_stdio(false);
    cin >> n;
    for(int i = 1;i<=n;++i)
        cin >> all[i];
    string name,name2;
    int t1,t2,give;
    while(cin >> name)
    {
        cin >> t1 >> t2;
        money[name] = t1;
        if(t2 == 0)
            continue;
        give = t1/t2;
        money[name] = give * t2;
        for(;t2;--t2)
        {
            cin >> name2;
            getmoney[name2] += give;
        }
        give *= t2;
    }
    for(int i = 1;i<=n;++i)
        cout << all[i] << ' ' << getmoney[all[i]] - money[all[i]] << '\n';
    return 0;
}