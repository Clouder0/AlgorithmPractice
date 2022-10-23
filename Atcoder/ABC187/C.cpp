#include <iostream>
#include <set>
using namespace std;
int n;
set<string> a, b;
int main()
{
    cin >> n;
    for (int i = 1; i <= n; ++i) 
    {
        string t;
        cin >> t;
        if(t[0] == '!') t = t.substr(1,t.length() - 1),b.insert(t);
        else a.insert(t);
        if(a.find(t) != a.end() && b.find(t) != b.end()) {cout << t << endl;return 0;}
    }
    cout << "satisfiable";
    return 0;
}