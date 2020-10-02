#include "pch.h"
#include <thread>
#include <cstdlib>
using namespace std;
using namespace rapidjson;

/*
analysis
O(f1)=O(N^2+N^3+3*N^4)
O(f2)=O(N+N^2)
O(f3)=O(N)
*/

//const LL N = 6000;

int __cdecl random(LL x)
{
    return (rand() + rand() + rand() + rand() + rand() + rand() + rand() + rand() + rand() + rand() + rand() + rand() + rand() + rand() + rand() + rand() + rand() + rand()) % x;
}

Document anser(kObjectType);
Value V1(kObjectType), V2(kObjectType), V3(kObjectType);

void f1();
void f2();
void f3();

int main()
{
    srand(clock());
    thread th1(f1);
    thread th2(f2);
    thread th3(f3);
    th1.join();
    th2.join();
    th3.join();
    // f1();
    // cout << "f1 done." << endl;
    // f2();
    // cout << "f2 done." << endl;
    // f3();
    // cout << "f3 done." << endl;

    anser.AddMember(Value("f1"), V1, anser.GetAllocator());
    anser.AddMember(Value("f2"), V2, anser.GetAllocator());
    anser.AddMember(Value("f3"), V3, anser.GetAllocator());

    FILE *fp;
    fp = fopen("2.7anser.json", "w");
    char writeBuffer[65536];
    FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
    Writer<FileWriteStream> writer(os);
    anser.Accept(writer);
    fclose(fp);

    return 0;
}

void f1()
{
    clock_t start, end;

    const LL N[] = {250, 500, 1000, 2000};

    for (LL I = 0; I < 4; I++)
    {
        LL *A;
        A = new LL[N[I]];
        start = clock();
        for (LL i = 0; i < N[I]; i++)
        {
            LL temp = random(N[I]);
            LL j;
            for (j = 0; j < i; j++)
                if (temp == A[j])
                    break;
            if (j == i)
                A[i] = temp;
            else
                i--;
        }
        end = clock();

        Value anser_data(kObjectType);
        anser_data.AddMember(Value("Time"), (double)(end - start) / CLOCKS_PER_SEC, anser.GetAllocator());
        char keystr[10];
        sprintf(keystr, "%lld", N[I]);
        V1.AddMember(Value(keystr, anser.GetAllocator()), anser_data, anser.GetAllocator());
        delete[] A;
        cout << "f1 done" << N[I] << endl;
    }

    // for (LL i = 0; i < N; i++)
    //     anser_data.PushBack(A[i], anser.GetAllocator());
    // V1.AddMember(Value("anser"), anser_data, anser.GetAllocator());
}

void f2()
{
    clock_t start, end;

    const LL N[] = {2500, 10000, 20000, 40000, 80000};
    for (LL I = 0; I < 5; I++)
    {
        LL *A;
        A = new LL[N[I]];
        bool *used;
        used = new bool[N[I]];
        for (LL i = 0; i < N[I]; i++)
            used[i] = false;
        start = clock();
        for (LL i = 0; i < N[I]; i++)
        {
            LL temp = random(N[I]);
            if (!used[temp])
            {
                A[i] = temp;
                used[temp] = true;
            }
            else
                i--;

            // if (i == 32767)
            // {
            //     for (LL t = 0; t < N[I]; t++)
            //     {
            //         if (!used[t])
            //             cout << "has false: " << t << endl;
            //     }
            //     cout << "used[60000]: " << used[60000] << endl;
            // }
        }
        end = clock();

        Value anser_data(kObjectType);
        anser_data.AddMember(Value("Time"), (double)(end - start) / CLOCKS_PER_SEC, anser.GetAllocator());
        char keystr[10];
        sprintf(keystr, "%lld", N[I]);
        V2.AddMember(Value(keystr, anser.GetAllocator()), anser_data, anser.GetAllocator());
        delete[] A;
        delete[] used;
        cout << "f2 done" << N[I] << endl;
    }

    // for (LL i = 0; i < N; i++)
    //     anser_data.PushBack(A[i], anser.GetAllocator());
    // V2.AddMember(Value("anser"), anser_data, anser.GetAllocator());
}

void f3()
{
    clock_t start, end;
    const LL N[] = {10000, 20000, 40000, 80000, 160000, 320000, 640000};

    for (LL I = 0; I < 7; I++)
    {
        LL *A;
        A = new LL[N[I]];

        start = clock();
        for (LL i = 0; i < N[I]; i++)
            A[i] = i;

        for (LL i = 0; i < N[I]; i++)
        {
            LL temp = A[i];
            LL temp2 = random(N[I]);
            A[i] = A[temp2];
            A[temp2] = temp;
        }
        end = clock();

        Value anser_data(kObjectType);
        anser_data.AddMember(Value("Time"), (double)(end - start) / CLOCKS_PER_SEC, anser.GetAllocator());
        char keystr[10];
        sprintf(keystr, "%lld", N[I]);
        V3.AddMember(Value(keystr, anser.GetAllocator()), anser_data, anser.GetAllocator());
        delete[] A;

        cout << "f3 done" << N[I] << endl;
    }

    // for (LL i = 0; i < N; i++)
    //     anser_data.PushBack(A[i], anser.GetAllocator());
    // V3.AddMember(Value("anser"), anser_data, anser.GetAllocator());
}