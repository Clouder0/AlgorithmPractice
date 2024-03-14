#include <cstdio>

const int mod = 1e9 + 7;
int n;
const int maxn = 1e7 + 100;
int f[maxn][4];
inline int add(int a, int b) {
    return (a + b) % mod;
}
int main() {
    scanf("%d", &n);
    // 0-a ,1-b, 2-c, 3-d
    f[0][3] = 1;
    for(int i = 1;i<=n;++i) {
        f[i][0] = add(add(f[i-1][1],f[i-1][2]),f[i-1][3]);
        f[i][1] = add(add(f[i-1][0],f[i-1][2]),f[i-1][3]);
        f[i][2] = add(add(f[i-1][1],f[i-1][0]),f[i-1][3]);
        f[i][3] = add(add(f[i-1][0],f[i-1][1]),f[i-1][2]);
    }
    printf("%d\n",f[n][3]);
    return 0;
}