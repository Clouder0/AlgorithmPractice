#include <iostream>
#include <string>
using namespace std;
int n, sum, cnt;
string all;
bool flag;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for (; n; --n)
    {
        cin >> all;
        flag = false;
        cnt = sum = 0;
        for (string::iterator it = all.begin(); it != all.end(); ++it)
        {
            if (*it == '0')
                flag = true;
            if (!((*it - '0') % 2))
                ++cnt;
            sum += *it - '0';
        }
        if (sum != 0 && (sum % 3 || !flag || cnt < 2))
        {
            cout << "cyan" << endl;
            continue;
        }
        else
            cout << "red" << endl;
    }
    return 0;
}