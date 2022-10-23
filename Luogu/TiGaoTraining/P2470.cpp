#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 60;
int n;
char s[maxn];
int w[maxn][maxn],g[maxn];
unsigned long long prod[maxn], hash[maxn];
unsigned long long gethash(int l, int r) { return hash[r] - hash[l - 1] * prod[r - l + 1]; }
int main()
{
    scanf("%s",s + 1);
    n = strlen(s + 1);
    hash[0] = prod[0] = 1;
    for (int i = 1; i <= n; ++i) hash[i] = hash[i - 1] * 133 + s[i] - 'a' + 1, prod[i] = prod[i - 1] * 133;
    memset(w,0x3f,sizeof(w));
    w[1][1] = 1;
    for (int i = 2; i <= n; ++i) w[i][i] = 2;//M and itself
    for (int i = 1; i <= n; ++i) 
        for (int j = i + 1; j <= n; ++j)
        {
            w[i][j] = min(w[i][j], w[i][j - 1] + 1);  //append one
            int mid = i + j >> 1;
            if(((j - i) & 1) && gethash(i,mid) == gethash(mid + 1,j)) w[i][j] = min(w[i][j],w[i][mid] + 1);
        }
    for (int i = 1; i <= n; ++i) g[i] = i;
    for (int i = 1; i <= n; ++i) for(int j = 0;j<i;++j) g[i] = min(g[i],g[j] + w[j + 1][i]);
    printf("%d\n",g[n]);
    return 0;
}