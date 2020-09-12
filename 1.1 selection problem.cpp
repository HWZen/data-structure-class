#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include "C:\Users\HWZ\GitHub\rapidjson\include\rapidjson\reader.h"
#include "C:\Users\HWZ\GitHub\rapidjson\include\rapidjson\document.h"
#include "C:\Users\HWZ\GitHub\rapidjson\include\rapidjson\writer.h"
#include "C:\Users\HWZ\GitHub\rapidjson\include\rapidjson\stringbuffer.h"
using namespace std;
using namespace rapidjson;

int main()
{
    clock_t startTime, endTime;

    ifstream file;
    file.open("1.1date.json");
    //将文件读入到ostringstream对象buf中
    ostringstream buf;
    char ch;
    while (buf && file.get(ch))
        buf.put(ch);
    //返回与流对象buf关联的字符串

    string jsonstr = buf.str();

    Document d;

    if (d.Parse(jsonstr.c_str()).HasParseError())
        throw string("parse error!\n");

    if (!d.IsObject())
        throw string("should be an object!\n");

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