#include <iostream>
#include <algorithm>
#include <ctime>
#include <thread>
#include <string.h>
#include "rapidjson\reader.h"
#include "rapidjson\document.h"
#include "rapidjson\writer.h"
#include "rapidjson\stringbuffer.h"
#include "rapidjson\filereadstream.h"
using namespace std;
using namespace rapidjson;

typedef long long LONG;
const char *arreytype = "arrey";

char readBuffer[23711748]; //记录矩阵json
Document d;                //记录字谜json、字典json、结果输出json

void Qsort(LONG arrey[], LONG hand, LONG last); //qsort(快排)
void Bubble(LONG arrey[], LONG Len);            //bubble(冒泡)

int main()
{
    clock_t start, stop;

    /*****************************/
    /*读入文件********************/
    cout << "loading data..." << endl;
    FILE *fp = fopen("sort_data.json", "r");
    FileReadStream is1(fp, readBuffer, sizeof(readBuffer));
    if (d.ParseStream(is1).HasParseError())
        throw string("parse error!\n");
    fclose(fp);
    cout << "load completed." << endl;

    LONG *arrey1, *arrey2;
    LONG size = d[arreytype].GetArray().Size();
    arrey1 = new LONG[size];
    arrey2 = new LONG[size];

    for (LONG i = 0; i < size; i++)
    {
        arrey1[i] = d[arreytype].GetArray()[i].GetInt64();
    }
    memcpy(arrey2, arrey1, sizeof(LONG) * size);

    cout << "data size: " << size << endl;

    start = clock();
    Qsort(arrey1, 0, size - 1);
    stop = clock();
    cout << "Qsort time: " << (double)(stop - start) / CLOCKS_PER_SEC << endl;

    if (size <= 100000)
    {
        start = clock();
        Bubble(arrey2, size);
        stop = clock();
        cout << "Bubble time: " << (double)(stop - start) / CLOCKS_PER_SEC << endl;
    }
    else
    {
        start = clock();
        sort(arrey2, arrey2 + size);
        stop = clock();
        cout << "STL::sort time: " << (double)(stop - start) / CLOCKS_PER_SEC << endl;
    }

    cout << "arrey2: " << arrey2[0] << " " << arrey2[size / 10] << " " << arrey2[2 * size / 10] << " " << arrey2[6 * size / 10] << " " << arrey2 << endl;
    cout << "arrey1: " << arrey1[0] << " " << arrey1[size / 10] << " " << arrey1[2 * size / 10] << " " << arrey1[6 * size / 10] << " " << arrey1 << endl;

    delete[] arrey1;
    delete[] arrey2;
}

void Qsort(LONG arrey[], LONG hand, LONG last)
{
    if (hand >= last)
        return;

    LONG T = arrey[hand];
    LONG F = hand;
    LONG L = last;

    while (F < L)
    {
        while (F < L && arrey[L] >= T)
        {
            --L;
        }
        arrey[F] = arrey[L];
        while (F < L && arrey[F] < T)
        {
            ++F;
        }
        arrey[L] = arrey[F];
    }
    arrey[F] = T;

    if ((last - hand) > 3000000)
    {
        thread thL(Qsort, arrey, hand, F - 1);
        thread thR(Qsort, arrey, L + 1, last);
        thL.join();
        thR.join();
    }
    else
    {
        Qsort(arrey, hand, F - 1);
        Qsort(arrey, L + 1, last);
    }
}

void Bubble(LONG arrey[], LONG Len)
{
    LONG temp;
    for (int i = 0; i < Len - 1; i++)
    {
        for (int j = 0; j < Len - 1 - i; j++)
        {
            if (arrey[j] > arrey[j + 1])
            {
                temp = arrey[j];
                arrey[j] = arrey[j + 1];
                arrey[j + 1] = temp;
            }
        }
    }
}