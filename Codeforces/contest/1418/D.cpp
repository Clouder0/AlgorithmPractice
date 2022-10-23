#include <cstdio>
#include <set>
using namespace std;
const int maxn = 1e5 + 100;
int n, m;
set<int> P;
multiset<int> D;
inline void addpoint(int x)
{
    set<int>::iterator it = P.insert(x).first;
    set<int>::iterator nex = it;
    ++nex;
    set<int>::iterator back;
    if (nex != P.end()) D.insert(*nex - x);
    if (it != P.begin()) back = it, D.insert(x - *(--back));
    if (it != P.begin() && nex != P.end()) D.erase(D.find(*nex - *back));
}
inline void delpoint(int x)
{
    set<int>::iterator it = P.find(x);
    set<int>::iterator nex = it;
    ++nex;
    set<int>::iterator back;
    if (nex != P.end()) D.erase(D.find(*nex - x));
    if (it != P.begin()) back = it, D.erase(D.find(x - *(--back)));
    if (it != P.begin() && nex != P.end()) D.insert(*nex - *back);
    P.erase(it);
}
inline void output()
{
    if (P.size() <= 2) return (void)(puts("0"));
    printf("%d\n", *P.rbegin() - *P.begin() - *D.rbegin());
}
int main()
{
    scanf("%d %d", &n, &m);
    for (int i = 1, x; i <= n; ++i) scanf("%d", &x), addpoint(x);
    output();
    while (m--)
    {
        int opt, x;
        scanf("%d %d", &opt, &x);
        if (opt) addpoint(x);
        else delpoint(x);
        output();
    }
    return 0;
}