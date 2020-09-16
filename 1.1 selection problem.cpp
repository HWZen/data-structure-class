#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include "rapidjson\reader.h"
#include "rapidjson\document.h"
#include "rapidjson\writer.h"
#include "rapidjson\stringbuffer.h"
#include "rapidjson\filereadstream.h"
using namespace std;
using namespace rapidjson;

char readBuffer[65536];

int main()
{
    clock_t startTime, endTime;

    Document d;

    FILE *fp = fopen("1.1date.json", "r");
    FileReadStream is1(fp, readBuffer, sizeof(readBuffer));
    if (d.ParseStream(is1).HasParseError())
        throw string("parse error!\n");
    fclose(fp);


    const bool Is_int = d["IS_int"].GetBool();
    int num = d["num"].GetInt();
    cout << "num: " << num << endl;
    const Value &DATA = d["data"];

    if (Is_int)
    {

        typedef int datatype;
        vector<datatype> vec;

        startTime = clock();

        for (SizeType i = 0; i < num / 2; i++)
            vec.push_back(DATA[i].GetInt());

        sort(vec.begin(), vec.end());

        cout << "vec.size: " << vec.size() << endl;

        for (SizeType i = num / 2; i < num; i++)
        {
            if (DATA[i].GetInt() < vec.back())
            {
                int tar = DATA[i].GetInt();
                int hand = 0;
                int last = num / 2 - 1;
                int p = (last + hand) / 2;
                while (!(
                    (vec[p] > tar && vec[p - 1] < tar) ||
                    (vec[p] == tar) ||
                    (last == hand)))
                {
                    if (vec[p] > tar)
                    {
                        last = p;
                        p = (last + hand - 1) / 2;
                    }
                    else
                    {
                        hand = p;
                        p = (last + hand + 1) / 2;
                    }
                }
                vec.insert(vec.begin() + p, tar);
                vec.pop_back();
            }
        }

        endTime = clock();

        cout << "anser: " << vec.back() << endl;
        cout << "runtime: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << 's' << endl;
        cout << endl;

        vec.clear();

        startTime = clock();

        for (SizeType i = 0; i < num; i++)
            vec.push_back(DATA[i].GetInt());

        sort(vec.begin(), vec.end());

        cout << "real anser: " << vec[num / 2 - 1] << endl;

        endTime = clock();
        cout << "runtime: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << 's' << endl;
    }
    else
    {
        typedef double datatype;
        vector<datatype> vec;

        startTime = clock();

        for (SizeType i = 0; i < num / 2; i++)
        {
            vec.push_back(DATA[i].GetDouble());
        }

        sort(vec.begin(), vec.end());
        for (SizeType i = num / 2; i < num; i++)
        {

            if (DATA[i].GetDouble() < vec.back())
            {
                double tar = DATA[i].GetDouble();
                int hand = 0;
                int last = num / 2 - 1;
                int p = (last + hand) / 2;
                while (!(
                    (vec[p] > tar && vec[p - 1] < tar) ||
                    (abs(vec[p] - tar) < 0.000001) ||
                    (last == hand)))
                {
                    if (vec[p] > tar)
                    {
                        last = p;
                        p = (last + hand - 1) / 2;
                    }
                    else
                    {
                        hand = p;
                        p = (last + hand + 1) / 2;
                    }
                }
                vec.insert(vec.begin() + p, tar);
                vec.pop_back();
            }
        }

        endTime = clock();

        cout << "anser: " << vec.back() << endl;
        cout << "runtime: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << 's' << endl;
        cout << endl;

        vec.clear();

        startTime = clock();

        for (SizeType i = 0; i < num; i++)
            vec.push_back(DATA[i].GetDouble());

        sort(vec.begin(), vec.end());

        cout << "real anser: " << vec[num / 2 - 1] << endl;

        endTime = clock();
        cout << "runtime: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << 's' << endl;
    }

    return 0;
}