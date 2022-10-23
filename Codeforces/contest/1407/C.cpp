#include <iostream>
using namespace std;
const int maxn = 1e4 + 100;
int n,ans[maxn],maxx;
inline int ask(int x,int y)
{
    cout << "? " << x << " " << y << endl;
    int res;
    cin >> res;
    return res;
}
int main()
{
    cin >> n;
    maxx = 1;
    for(int i = 2;i<=n;++i)
    {
        int a = ask(maxx,i);
        int b = ask(i,maxx);
        if(a > b)
        {
            //maxx < i
            ans[maxx] = a;
            maxx = i;
        }
        else ans[i] = b;
    }
    ans[maxx] = n;
    cout << "! ";
    for (int i = 1; i <= n; ++i) cout << ans[i] << " ";
    cout << endl;
    return 0;
}