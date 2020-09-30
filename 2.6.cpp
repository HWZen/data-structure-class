#include "pch.h"
#include <thread>
#include <sstream>
using namespace std;
using namespace rapidjson;

/*
O(f1)=O(N)
O(f2)=O(N^2)
O(f3)=O(N^3)
O(f4)=O(N^2)
O(f5)=O(N^4)
O(f6)=O(N^3+N)
*/

const LONG First = 30000;
const LONG Last = 65000;
const LONG Mid = 5000;

void f1();
void f2();
void f3();
void f4();
void f5();
void f6();

rapidjson::Document d(kObjectType);
rapidjson::Value V[6];

int main()
{
    for (int i = 0; i < 6; i++)
        V[i].SetObject();

    thread th1(f1);
    thread th2(f2);
    thread th3(f3);
    thread th4(f4);
    thread th5(f5);
    thread th6(f6);
    th1.join();
    th2.join();
    th3.join();
    th4.join();
    th5.join();
    th6.join();

    cout << "calculated." << endl;

    for (int i = 0; i < 6; i++)
    {
        char key[4];
        sprintf(key, "F%d", i);
        d.AddMember(rapidjson::Value(key, d.GetAllocator()), V[i], d.GetAllocator());
    }

    FILE *fp;
    fp = fopen("2.6anser.json", "w");
    char writeBuffer[65536];
    FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
    Writer<FileWriteStream> writer(os);
    d.Accept(writer);
    fclose(fp);
    return 0;
}

void f1()
{
    clock_t start, end;

    for (LONG N = First * 500; N < Last * 500; N += Mid * 500)
    {
        start = clock();
        LONG sum = 0;
        for (LONG i = 0; i < N; i++)
            sum++;
        end = clock();
        cout << "f1completed: " << N << endl;

        V[0].AddMember(Value(to_string(N).c_str(), d.GetAllocator()), (double)(end - start) / CLOCKS_PER_SEC, d.GetAllocator());
    }
}

void f2()
{
    clock_t start, end;

    for (LONG N = First; N < Last; N += Mid)
    {
        start = clock();
        LONG sum = 0;
        for (LONG i = 0; i < N; i++)
            for (LONG j = 0; j < N; j++)
                sum++;
        end = clock();
        cout << "f2completed: " << N << endl;

        V[1].AddMember(Value(to_string(N).c_str(), d.GetAllocator()), (double)(end - start) / CLOCKS_PER_SEC, d.GetAllocator());
    }
}

void f3()
{
    clock_t start, end;

    for (LONG N = First / 200; N < Last / 200; N += Mid / 200)
    {
        start = clock();
        LONG sum = 0;
        for (LONG i = 0; i < N; i++)
            for (LONG j = 0; j < N * N; j++)
                sum++;
        end = clock();
        cout << "f3completed: " << N << endl;

        V[2].AddMember(Value(to_string(N).c_str(), d.GetAllocator()), (double)(end - start) / CLOCKS_PER_SEC, d.GetAllocator());
    }
}

void f4()
{
    clock_t start, end;

    for (LONG N = First * 3; N < Last * 3; N += Mid * 3)
    {
        start = clock();
        LONG sum = 0;
        for (LONG i = 0; i < N; i++)
            for (LONG j = 0; j < i; j++)
                sum++;
        end = clock();
        cout << "f4completed: " << N << endl;

        V[3].AddMember(Value(to_string(N).c_str(), d.GetAllocator()), (double)(end - start) / CLOCKS_PER_SEC, d.GetAllocator());
    }
}

void f5()
{
    clock_t start, end;

    for (LONG N = First / 250; N < Last / 250; N += Mid / 250)
    {
        start = clock();
        LONG sum = 0;
        for (LONG i = 0; i < N; i++)
            for (LONG j = 0; j < i * i; j++)
                for (int k = 0; k < j; k++)
                    sum++;
        end = clock();
        cout << "f5completed: " << N << endl;

        V[4].AddMember(Value(to_string(N).c_str(), d.GetAllocator()), (double)(end - start) / CLOCKS_PER_SEC, d.GetAllocator());
    }
}

void f6()
{
    clock_t start, end;

    for (LONG N = First / 100; N < Last / 100; N += Mid / 100)
    {
        start = clock();
        LONG sum = 0;
        for (LONG i = 0; i < N; i++)
            for (LONG j = 0; j < i * i; j++)
                if (j % i == 0)
                    for (LONG k = 0; k < j; k++)
                        sum++;
        end = clock();
        cout << "f6completed: " << N << endl;

        V[5].AddMember(Value(to_string(N).c_str(), d.GetAllocator()), (double)(end - start) / CLOCKS_PER_SEC, d.GetAllocator());
    }
}

/*
{
    "F0": {
        "15000000": 0.029,
        "17500000": 0.034,
        "20000000": 0.039,
        "22500000": 0.045,
        "25000000": 0.05,
        "27500000": 0.054,
        "30000000": 0.059
    },
    "F1": {
        "30000": 1.713,
        "35000": 2.344,
        "40000": 3.051,
        "45000": 3.865,
        "50000": 4.754,
        "55000": 5.774,
        "60000": 6.904
    },
    "F2": {
        "150": 0.008,
        "175": 0.011,
        "200": 0.017,
        "225": 0.024,
        "250": 0.033,
        "275": 0.042,
        "300": 0.054
    },
    "F3": {
        "90000": 7.751,
        "105000": 10.569,
        "120000": 13.837,
        "135000": 17.585,
        "150000": 21.759,
        "165000": 26.37,
        "180000": 31.55
    },
    "F4": {
        "120": 3.406,
        "140": 7.25,
        "160": 14.313,
        "180": 25.338,
        "200": 42.592,
        "220": 66.67,
        "240": 101.843
    },
    "F5": {
        "300": 1.95,
        "350": 3.572,
        "400": 6.097,
        "450": 9.821,
        "500": 15.006,
        "550": 21.964,
        "600": 31.267
    }
}
*/