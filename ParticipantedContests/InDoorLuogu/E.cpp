#include <cstdio>
#include <iostream>
#include <string>
using namespace std;
string nums[11][6] = 
{
    {
        "XXX",
        "X.X",
        "X.X",
        "X.X",
        "XXX"
    },
    {
        "..X",
        "..X",
        "..X",
        "..X",
        "..X"
    },
    {
        "XXX",
        "..X",
        "XXX",
        "X..",
        "XXX"
    },
    {
        "XXX",
        "..X",
        "XXX",
        "..X",
        "XXX"
    },
    {
        "X.X",
        "X.X",
        "XXX",
        "..X",
        "..X"
    },
    {
        "XXX",
        "X..",
        "XXX",
        "..X",
        "XXX"
    },
    {
        "XXX",
        "X..",
        "XXX",
        "X.X",
        "XXX"
    },
    {
        "XXX",
        "..X",
        "..X",
        "..X",
        "..X"
    },
    {
        "XXX",
        "X.X",
        "XXX",
        "X.X",
        "XXX"
    },
    {
        "XXX",
        "X.X",
        "XXX",
        "..X",
        "XXX"
    },
};
int n;
char s[10000];
int main()
{
    scanf("%d",&n);
    scanf("%s",s+1);
    for(int k = 0;k<5;++k)
    {
        for(int i = 1;i<n;++i)
            cout << nums[s[i]-48][k] << '.';
        cout << nums[s[n]-48][k];
        putchar('\n');
    }
    return 0;
}