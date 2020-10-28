#include <iostream>
#include <stdio.h>
using namespace std;

struct HEAP
{
    int a;
    int b;
    int p = -1;
    int v;
} * heap;

int length = 0;

void swap(int p)
{
    heap[0] = heap[p / 2];
    heap[p / 2] = heap[p];
    heap[p] = heap[0];
}

void swap(int p, int p2)
{
    heap[0] = heap[p2];
    heap[p2] = heap[p];
    heap[p] = heap[0];
}

void insert(const HEAP &h)
{
    length++;
    heap[length] = h;
    int p = length;
    while (heap[p / 2].v > heap[p].v && p > 1)
    {
        swap(p);
        p = p / 2;
    }
}

void down(int k)
{
    int t = k;
    while (true)
    {
        if ((k * 2) <= length)
        {
            if (heap[k * 2].v < heap[t].v)
                t = k * 2;
        }
        if ((k * 2 + 1) <= length)
        {
            if (heap[k * 2 + 1].v < heap[t].v)
                t = k * 2 + 1;
        }
        if (t != k)
        {
            swap(t, k);
            k = t;
        }
        else
            return;
    }
}

void del()
{

    heap[1] = heap[length];
    length--;
    down(1);
}

int main()
{
    int N, k;
    long long sum = 0;

    scanf("%d%d", &N, &k);
    heap = new HEAP[N + 2];
    HEAP temp;
    while (N--)
    {
        scanf("%d%d", &temp.a, &temp.b);
        int t = temp.a / (2 * temp.b);
        temp.p = (temp.a - 2 * temp.b * t) > 2 * temp.b * (t + 1) - temp.a ? t + 1 : t;
        if (temp.a < temp.b || temp.p <= 0)
            continue;
        k -= temp.p;
        temp.v = temp.a + temp.b - 2 * temp.b * temp.p;
        insert(temp);
    }

    while (k < 0)
    {
        heap[1].p--;
        k++;
        if (heap[1].p == 0)
            del();
        else
        {
            heap[1].v = heap[1].a + heap[1].b - 2 * heap[1].b * heap[1].p;
            down(1);
        }
    }

    for (int i = 1; i <= length; i++)
        sum += (long long)heap[i].p * (long long)((long long)heap[i].a - (long long)heap[i].b * (long long)heap[i].p);

    printf("%lld", sum);

    delete[] heap;

    return 0;
}
