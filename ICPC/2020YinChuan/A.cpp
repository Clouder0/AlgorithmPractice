#include <algorithm>
#include <cstdio>
struct node
{
    int x, y, z;
    bool operator<(const node& other)
    {
        if (x != other.x) return x < other.x;
        if (y != other.y) return y < other.y;
        return z < other.z;
    }
} A[110], B[110];
int n;
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d%d%d", &A[i].x, &A[i].y, &A[i].z), B[i] = A[i];
    for (int i = 1; i <= n; ++i) B[i].x = 0;
    std::sort(B + 1, B + 1 + n);
    int res = 1, resi = 1, now = 1;
    for (int i = 2; i <= n; ++i)
    {
        if (!(B[i].x == B[i - 1].x && B[i].y == B[i - 1].y && B[i].z == B[i - 1].z)) ++now;
    }
    if (now > res) resi = 1, res = now;
    for (int i = 1; i <= n; ++i) B[i] = A[i], B[i].y = 0;
    std::sort(B + 1, B + 1 + n);
    now = 1;
    for (int i = 2; i <= n; ++i)
        if (!(B[i].x == B[i - 1].x && B[i].y == B[i - 1].y && B[i].z == B[i - 1].z)) ++now;
    if (now > res) resi = 2, res = now;
    for (int i = 1; i <= n; ++i) B[i] = A[i], B[i].z = 0;
    std::sort(B + 1, B + 1 + n);
    now = 1;
    for (int i = 2; i <= n; ++i)
        if (!(B[i].x == B[i - 1].x && B[i].y == B[i - 1].y && B[i].z == B[i - 1].z)) ++now;
    if (now > res) resi = 3, res = now;
    if (resi == 1) puts("X");
    else if (resi == 2) puts("Y");
    else puts("Z");
    return 0;
}