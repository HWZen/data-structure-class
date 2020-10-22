#include <iostream>
#include <stdio.h>
#include <ctime>
#include <stdlib.h>

using namespace std;

class Treap;
typedef Treap *nT;
nT root;
class Treap
{
private:
    long long key;
    int son;                      //儿子数
    int weight;                   //权值
    nT L;                         //左指针
    nT R;                         //右指针
    nT F;                         //父指针
    void rotate(nT p, char D);    //旋转
    long long rank(nT p, int &n); //查找

    void maintain()
    {
        son = 1;
        if (L != NULL)
            son += L->son;
        if (R != NULL)
            son += R->son;
    }

public:
    Treap()
    {
        key = -1;
        L = R = F = NULL;
        son = 0;
        weight = rand();
    }
    Treap(int Key)
    {
        this->key = Key;
        weight = rand();
        L = R = F = NULL;
        son = 1;
    }
    void insert(nT p, long long key);
    void insert(long long Key) { insert(root, Key); }
    long long rank(int n) { return rank(root, n); }
};

void Treap::insert(nT p, long long Key)
{
    if (p->key == -1)
    {
        p->key = Key;
        son++;
        return;
    }
    if (p->key > Key)
    {
        if (p->L == NULL)
        {
            p->L = new Treap(Key);
            p->L->F = p;
            if (p->L->weight < p->weight)
                rotate(p, 'R');
            else
                p->maintain();
        }
        else
        {
            insert(p->L, Key);
            if (p->L->weight < p->weight)
                rotate(p, 'R');
            else
                p->maintain();
        }
        return;
    }
    else
    {
        if (p->R == NULL)
        {
            p->R = new Treap(Key);
            p->R->F = p;
            if (p->R->weight < p->weight)
                rotate(p, 'L');
            else
                p->maintain();
        }
        else
        {
            insert(p->R, Key);
            if (p->R->weight < p->weight)
                rotate(p, 'L');
            else
                p->maintain();
        }
    }
}

void Treap::rotate(nT p, char D)
{
    if (D == 'L')
    {
        nT b = p->R;
        b->F = p->F;
        if (p->F != NULL)
        {
            if (p->F->L == p)
                p->F->L = b;
            else
                p->F->R = b;
        }
        else
        {
            root = b;
        }
        p->R = b->L;
        if (b->L != NULL)
            b->L->F = p;
        b->L = p;
        p->F = b;
        p->maintain();
        b->maintain();
    }
    else
    {
        nT b = p->L;
        b->F = p->F;
        if (p->F != NULL)
        {
            if (p->F->L == p)
                p->F->L = b;
            else
                p->F->R = b;
        }
        else
        {
            root = b;
        }
        p->L = b->R;
        if (b->R != NULL)
            b->R->F = p;
        b->R = p;
        p->F = b;
        p->maintain();
        b->maintain();
    }
}

long long Treap::rank(nT p, int &n)
{
    if (p->R == NULL && n == 1)
        return p->key;

    if (p->R != NULL)
    {
        if (p->R->son == n - 1)
            return p->key;
        else if (p->R->son >= n)
            return rank(p->R, n);

        n -= p->R->son + 1;
        if (p->L != NULL && p->L->son >= n)
            return rank(p->L, n);
    }
    else if (p->L != NULL && p->L->son >= --n)
        return rank(p->L, n);

    return -1;
}

int main()
{
    srand(clock());
    int m, q, t, t2;
    Treap git;
    root = &git;
    scanf("%d%d", &m, &q);
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &t);
        git.insert(t);
    }

    while (q--)
    {
        scanf("%d%d", &t, &t2);
        if (t == 1)
        {
            long long temp = git.rank(t2);
            printf("%lld\n", temp);
        }
        else
            git.insert(t2);
    }

    return 0;
}