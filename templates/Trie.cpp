#include <cstdio>
#include <cstring>
const int maxn = 1e6 + 100;
struct Trie
{
    int to[maxn][26], cnt;
    bool end[maxn];//marks if there exists a string ends at that node.
    void insert(char *s)
    {
        int p = 0;
        for (; *s != '\0'; ++s)
        {
            int c = *s - 'a';
            if (!to[p][c]) to[p][c] = ++cnt;  //create a new edge to that node
            p = to[p][c];
        }
        end[p] = 1;//marks that a string ends here
    }
    bool find(char *s)
    {
        int p = 0;
        for (; *s != '\0'; ++s)
        {
            int c = *s - 'a';
            if (!to[p][c]) return 0;  //no such edge exists, means that no matching.
            p = to[p][c];
        }
        return end[p];
    }
} T;
int main()
{

    return 0;
}