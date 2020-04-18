#include "cstdio"
#include "iostream"
#include "cctype"
using namespace std;
int heap_size, n;
int heap[30001];
inline int readint()
{
    char c = getchar();
    while (!isdigit(c))
        c = getchar();
    int x = 0;
    while (isdigit(c))
    {
        x = x * 10 + c - '0';
        c = getchar();
    }
    return x;
}
int buf[105];
inline void writeint(int i)
{
    int p = 0;
    if (i == 0)
        p++;
    else
        while (i)
        {
            buf[p++] = i % 10;
            i /= 10;
        }
    for (int j = p - 1; j >= 0; j--)
        putchar('0' + buf[j]);
}
void swap(int &a, int &b)
{
    int t = a;
    a = b;
    b = t;
}
void put(int d)
{
    int now, next;
    heap[++heap_size] = d;
    now = heap_size;
    while (now > 1)
    {
        next = now >> 1;
        if (heap[now] >= heap[next])
            return;
        swap(heap[now], heap[next]);
        now = next;
    }
}
int del()
{
    int now, next, res;
    res = heap[1];
    heap[1] = heap[heap_size--];
    now = 1;
    while (now * 2 <= heap_size)
    {
        next = now * 2;
        if (next < heap_size && heap[next + 1] < heap[next])
            next++;
        if (heap[now] <= heap[next])
            return res;
        swap(heap[now], heap[next]);
        now = next;
    }
}
int get()
{
    return heap[1];
}
void work()
{
    n = readint();
    for (int i = 1; i <= n; i++)
    {
        int x;
        x = readint();
        if (x == 1)
        {
            x = readint();
            put(x);
        }
        else if (x == 2)
        {
            writeint(get());
            putchar('\n');
        }
        else
            del();
        printf("Heap: ");
        for(int i = 1;i<=heap_size;++i)
            printf("%d ",heap[i]);
        putchar('\n');
    }
}
int main()
{
    work();
    return 0;
}
