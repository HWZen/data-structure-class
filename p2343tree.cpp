#include <iostream>
#include <stdio.h>
#include <ctime>
#include <stdlib.h>

using namespace std;

int cnt = 0;

class Treap;

typedef Treap * nT;
class Treap
{
private:
    long long key;
    int weight;//权值
    nT L;//左指针
    nT R;//右指针
    nT F;//父指针
    int son;//儿子数
    void rotate(nT p,char D);//旋转
    long long rank(nT p, int &n);//查找

    void maintain()
    {
        son = 1;
        if(L!=NULL)
            son += L->son;
        if(R!=NULL)
            son += R->son;
    }

public:
    Treap()
    {
        key = -1;
        L = R = F = NULL;
        son = 0;
        weight = cnt++;
    }
    Treap(int Key)
    {
        this->key = Key;
        weight = cnt++;
        L = R = F = NULL;
        son = 1;
    }
    void insert(nT p ,long long key);
    void insert(long long  Key) { insert(this, Key); }
    long long rank(int n) { return rank(this, n); }
};

void Treap::insert(nT p,long long Key)
{
    if(p->key==-1)
    {
        p->key = Key;
        son++;
        return;
    }
    if(p->key>Key)
    {
        if(p->L==NULL)
        {
            p->L = new Treap(Key);
            p->L->F = p;
            // nT t = p;
            // while (t!=NULL)
            // {
            //     t->son++;
            //     t = t->F;
            // }
            p->maintain();
        }
        else
        {
            insert(p->L, Key);
            if(p->L->weight>p->weight)
                rotate(p,'L');
            p->maintain();
        }
        return;
    }
    else if(p->key<=Key)
    {
        if(p->R==NULL)
        {
            p->R = new Treap(Key);
            p->R->F = p;
            // nT t = p;
            // while (t!=NULL)
            // {
            //     t->son++;
            //     t = t->F;
            // }
            p->maintain();
        }
        else
        {
            insert(p->R, Key);
            if(p->R->weight>p->weight)
                rotate(p, 'R');
            p->maintain();
        }
    }
}

void Treap::rotate(nT p,char D)
{
    if(D=='L')
    {
         nT k=p->R;
         p->R=k->L;
         p->maintain();
         k->maintain();
         k->L=p;
         p=k;
    }
    else
    {
         nT k=p->L;
         p->L=k->R;
         p->maintain();
         k->maintain();
         k->R=p;
         p=k;
    }
    
}

long long Treap::rank(nT p,int &n)
{
    if(p->R==NULL&&n==1)
        return p->key;

    if(p->R!=NULL)
    {
        if(p->R->son==n-2)
            return p->key;
        if(p->R->son>=n-1)
            return rank(p->R, n);
        else
        {
            n -= p->R->son + 2;
            if(p->L!=NULL&&p->L->son>n)
                return rank(p->L, n);
        }
        
    }
    else if(p->L!=NULL&&p->L->son>n-1)
        return rank(p->L, n);

    return -1;
}

int main()
{
    int m, q, t, t2;
    Treap git;
    scanf("%d%d", &m, &q);
    for (int i = 0; i < m;i++)
    {
        scanf("%d", &t);
        git.insert(t);
    }

    while (q--)
    {
        scanf("%d%d", &t, &t2);
        if(t==1)
        {
            long long temp = git.rank(t2);
            printf("%lld\n", temp);
        }
        else
            git.insert(t2);
    }

    return 0;
}