#include <cstdio>
#include <iostream>
using namespace std;
const int maxn = 1e3 + 100;
int n;
bool rowin(int l, int r)
{
    printf("? %d %d %d %d", l, r, 1, n);
    cout << endl;
    fflush(stdout);
    int t;
    cin >> t;
    return t != (r - l + 1);
}
bool colin(int l, int r)
{
    printf("? %d %d %d %d", 1, n, l, r);
    cout << endl;
    fflush(stdout);
    int t;
    cin >> t;
    return t != (r - l + 1);
}
int main()
{
    scanf("%d", &n);
    // choose row
    int l = 1, r = n, al = 1, ar = n;
    while (al != ar)
    {
        int mid = (l + r) >> 1;
        if (l == r)
        {
            al = l;
            break;
        }
        if (l + 1 == r)
        {
            if (rowin(l, l))
            {
                al = l;
                break;
            }
            else
            {
                al = r;
                break;
            }
        }
        if (rowin(l, mid))
            al = l, ar = mid, r = mid;
        else
            l = mid + 1;
    }
    int row = al;
    l = 1, r = n;
    al = 1, ar = n;
    while (al != ar)
    {
        int mid = (l + r) >> 1;
        if (l == r)
        {
            al = l;
            break;
        }
        if (l + 1 == r)
        {
            if (colin(l, l))
            {
                al = l;
                break;
            }
            else
            {
                al = r;
                break;
            }
        }

        if (colin(l, mid))
            al = l, ar = mid, r = mid;
        else
            l = mid + 1;
    }
    int col = al;
    printf("! %d %d\n", row, col);
    fflush(stdout);
    return 0;
}