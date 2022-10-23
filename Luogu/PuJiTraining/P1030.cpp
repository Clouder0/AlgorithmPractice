#include <iostream>
#include <string>
using namespace std;
string amid,alast;
void build(string mid,string last)
{
    if(mid.empty() || last.empty())
        return;
    char root = last[last.length()-1];
    putchar(root);
    int p = mid.find(root);
    build(mid.substr(0,p),last.substr(0,p));
    build(mid.substr(p+1),last.substr(p,last.length() - p - 1));
}
int main()
{
    cin >> amid >> alast;
    build(amid,alast);
    return 0;
}