#include <cstdio>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;
struct node
{
    string i, x, y;
    node()
    {
        i = string();
        x = string();
        y = string();
    }
} all[110];
int t, l, o, cnt;
__gnu_pbds::gp_hash_table<char, bool> ht;
int tInt(const string &a)
{
    static stringstream ss;
    ss.clear();
    ss << a;
    int r;
    ss >> r;
    return r;
}
void read(int &r)
{
    static char c;
    r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar())
        ;
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar())
        ;
}
int main()
{
    scanf("%d", &t);
    while (t--)
    {
        cnt = 0;
        ht.clear();
        scanf("%d", &l);
        char c = getchar();
        while (c != '(')
            c = getchar();
        c = getchar();
        if (c == 'n')
            read(o);
        else
            o = 0;
        while (c != '\n')
            c = getchar();
        char temp[2];
        int w = 0, ans = 0;
        bool flag = false;
        for (int i = 1; i <= l; ++i)
        {
            scanf("%s", temp);

            if (temp[0] == 'F')
            {
                if (flag)
                {
                    cin >> all[1].i >> all[1].x >> all[1].y;
                    continue;
                }
                ++cnt;
                cin >> all[cnt].i >> all[cnt].x >> all[cnt].y;
                if (ht[all[cnt].i[0]])
                {
                    printf("ERR\n");
                    flag = true;
                }
                ht[all[cnt].i[0]] = true;
                ans = w > ans ? w : ans;
                w = 0;
            }
            else
            {
                if(flag)
                    continue;
                if (cnt <= 0)
                {
                    printf("ERR\n");
                    flag = true;
                }
                ht[all[cnt].i[0]] = false;
                if (all[cnt].x[0] == 'n' && all[cnt].y[0] == 'n')
                {
                    --cnt;
                    if (cnt == 0)
                        ans = w > ans ? w : ans;
                    continue;
                }
                if (all[cnt].x[0] == 'n')
                {
                    w = 0;
                    --cnt;
                    if (cnt == 0)
                        ans = w > ans ? w : ans;
                    continue;
                }
                if (all[cnt].y[0] == 'n')
                {
                    ++w;
                    --cnt;
                    if (cnt == 0)
                        ans = w > ans ? w : ans;
                    continue;
                }
                int tx = tInt(all[cnt].x);
                int ty = tInt(all[cnt].y);
                if (tx > ty)
                {
                    w = 0;
                    --cnt;
                    if (cnt == 0)
                        ans = w > ans ? w : ans;
                    continue;
                }
                --cnt;
                if (cnt == 0)
                    ans = w > ans ? w : ans;
            }
        }
        if (flag)
            continue;
        if (cnt > 0)
        {
            printf("ERR\n");
            continue;
        }
        ans = w > ans ? w : ans;
        if (ans == o)
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}