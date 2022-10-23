#include <iostream>
#include <cstring>
#include <string>
#include <queue>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
string A, B;
string rules[8][3];
int cnt = 1;
struct node
{
    int step;
    string now;
    node() {}
    node(int ss, string n) : step(ss), now(n) {}
};
queue<node> q;
__gnu_pbds::gp_hash_table<string, bool> ht;
int main()
{
    cin >> A >> B;
    while (cin >> rules[cnt][1] >> rules[cnt][2])
        ++cnt;
    --cnt;
    q.push((node){0, A});
    node t;
    string temp;
    int pos;
    ht[A] = true;
    while (!q.empty())
    {
        t = q.front();
        q.pop();
        if (t.step > 10)
        {
            printf("NO ANSWER!");
            return 0;
        }
        if (t.now == B)
        {
            printf("%d", t.step);
            return 0;
        }
        for (int i = 1; i <= cnt; ++i)
        {
            temp = t.now;
            for (int pos = t.now.find(rules[i][1]); pos != -1; pos = t.now.find(rules[i][1], pos + 1))
            {
                temp = t.now;
                temp.replace(pos, rules[i][1].size(), rules[i][2]);
                if (!ht[temp])
                    q.push(node(t.step + 1, temp)), ht[temp] = true;
            }
        }
    }
    printf("NO ANSWER!");
    return 0;
}