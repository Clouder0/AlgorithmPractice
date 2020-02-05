#include <cstdio>
#include <iostream>
using namespace std;
int n;
int main()
{
    cin >> n;
    cout << "Today, I ate "<< n;
    if(n > 1)
        cout << " apples.";
    else
        cout << " apple.";
    return 0;
}