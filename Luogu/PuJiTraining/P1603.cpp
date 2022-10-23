#include <cstdio>
#include <iostream>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <string>
#include <algorithm>
using namespace std;
__gnu_pbds::gp_hash_table<string, int> ht;
void init()
{
    ht["one"] = 1;
    ht["two"] = 2;
    ht["three"] = 3;
    ht["four"] = 4;
    ht["five"] = 5;
    ht["six"] = 6;
    ht["seven"] = 7;
    ht["eight"] = 8;
    ht["nine"] = 9;
    ht["ten"] = 10;
    ht["eleven"] = 11;
    ht["twelve"] = 12;
    ht["thirteen"] = 13;
    ht["fourteen"] = 14;
    ht["fifteen"] = 15;
    ht["sixteen"] = 16;
    ht["seventeen"] = 17;
    ht["eighteen"] = 18;
    ht["nineteen"] = 19;
    ht["twenty"] = 20;
    ht["a"] = 1;
    ht["both"] = 2;
    ht["another"] = 2;
    ht["first"] = 1;
    ht["second"] = 2;
    ht["third"] = 3;
}
string temp;
int all[7];
int cnt;
int main()
{
    init();
    int t;
    cin.tie(0);
    ios::sync_with_stdio(false);
    for(int i = 1;i<=6;++i)
    {
        cin >> temp;
        t = ht[temp];
        if(t)
            all[++cnt] = t*t;
    }
    if(cnt == 0)
    {
        putchar('0');
        return 0;
    }
    sort(all+1,all+1+cnt);
    printf("%d",all[1]);
    for(int i = 2;i<=cnt;++i)
        printf("%.2d",all[i]);
    return 0;
}