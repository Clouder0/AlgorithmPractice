#include <iostream>
#include <set>
#include <map>
using namespace std;
int n;
map<string,string> fa;
set<string> all;
int main()
{
    cin >> n;
    while(n--)
    {
        string a,b;
        cin >> a >> b;
        fa[b] = a;
        all.insert(a),all.insert(b);
    }
    for(set<string>::iterator it = all.begin();it!=all.end();++it)
    {
        map<string,string>::iterator f = fa.find(*it);
        if(f == fa.end())
        {
            puts("0");
            return 0;
        }
    }
    puts("1");
    return 0;
}