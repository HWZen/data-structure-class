#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <thread>
#include "rapidjson\reader.h"
#include "rapidjson\document.h"
#include "rapidjson\writer.h"
#include "rapidjson\stringbuffer.h"
#include "rapidjson\filewritestream.h"
#include "rapidjson\filereadstream.h"
using namespace std;
using namespace rapidjson;

char readBuffer[65536];
char readBuffer2[23164388];
Document d, dicstionary, Anser; //记录字谜json、字典json、结果输出json
char **matrix;                  //记录字谜矩阵
int Xnum;                       //矩阵宽
int Ynum;                       //矩阵长

//各方向便利函数
void W(int x, int y, Value &anser);
void S(int x, int y, Value &anser);
void A(int x, int y, Value &anser);
void D(int x, int y, Value &anser);
void WA(int x, int y, Value &anser);
void WD(int x, int y, Value &anser);
void SA(int x, int y, Value &anser);
void SD(int x, int y, Value &anser);

int main()
{
    //计时
    clock_t startTime, endTime;
    startTime = clock();

    /*****************************/
    /*读入文件********************/
    cout << "loading data..." << endl;
    FILE *fp = fopen("1.2data.json", "r");
    FileReadStream is1(fp, readBuffer, sizeof(readBuffer));
    if (d.ParseStream(is1).HasParseError())
        throw string("parse error!\n");
    fclose(fp);

    cout << "loading dictionary..." << endl;
    fp = fopen("dictionary_alpha_arrays.json", "r");
    FileReadStream is2(fp, readBuffer2, sizeof(readBuffer2));
    if (dicstionary.ParseStream(is2).HasParseError())
        throw string("parse error!\n");
    fclose(fp);
    cout << "loading completed." << endl;

    //记录矩阵长宽
    const Value &x = d["x"];
    Xnum = x.Size();
    Ynum = x[0].GetObject()["y"].Size();

    /**************************/
    /*建立矩阵******************/
    matrix = new char *[Xnum];

    for (int i = 0; i < Xnum; i++)
        matrix[i] = new char[Ynum];

    //写入矩阵
    for (int i1 = 0; i1 < Xnum; i1++)
    {
        const Value &y = x[i1].GetObject()["y"];
        for (int i2 = 0; i2 < Ynum; i2++)
        {
            matrix[i1][i2] = *(y[i2].GetString());
            cout << matrix[i1][i2] << " "; //打印矩阵
        }
        cout << endl;
    }

    /************************************/
    /*数据处理***************************/
    Anser.SetObject();
    for (int i1 = 0; i1 < Xnum; i1++)
    {
        for (int i2 = 0; i2 < Ynum; i2++)
        {
            Value anserW(kObjectType), anserS(kObjectType), anserA(kObjectType), anserD(kObjectType), anserWA(kObjectType), anserWD(kObjectType), anserSA(kObjectType), anserSD(kObjectType);
            //多线程处理
            thread thr1(W, i1, i2, ref(anserW));
            thread thr2(S, i1, i2, ref(anserS));
            thread thr3(A, i1, i2, ref(anserA));
            thread thr4(D, i1, i2, ref(anserD));
            thread thr5(WA, i1, i2, ref(anserWA));
            thread thr6(WD, i1, i2, ref(anserWD));
            thread thr7(SA, i1, i2, ref(anserSA));
            thread thr8(SD, i1, i2, ref(anserSD));
            thr1.join();
            thr2.join();
            thr3.join();
            thr4.join();
            thr5.join();
            thr6.join();
            thr7.join();
            thr8.join();

            //结果写入
            char keystr[10];
            sprintf(keystr, "(%d,%d)", i1, i2);
            Value key(keystr, Anser.GetAllocator());
            Value val(kObjectType);
            val.AddMember("anserW", anserW, Anser.GetAllocator());
            val.AddMember("anserS", anserS, Anser.GetAllocator());
            val.AddMember("anserA", anserA, Anser.GetAllocator());
            val.AddMember("anserD", anserD, Anser.GetAllocator());
            val.AddMember("anserWA", anserWA, Anser.GetAllocator());
            val.AddMember("anserWD", anserWD, Anser.GetAllocator());
            val.AddMember("anserSA", anserSA, Anser.GetAllocator());
            val.AddMember("anserSD", anserSD, Anser.GetAllocator());

            Anser.AddMember(key, val, Anser.GetAllocator());
        }
    }

    cout << "writting anser.json..." << endl;
    fp = fopen("anser.json", "w");
    char writeBuffer[65536];
    FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
    Writer<FileWriteStream> writer(os);
    Anser.Accept(writer);
    fclose(fp);
    cout << "writting completed." << endl;

    /***************************/
    /*析构矩阵*******************/
    for (int i = 0; i < Xnum; i++)
        delete[] matrix[i];
    delete[] matrix;

    endTime = clock();
    cout << "use time: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << endl;

    return 0;
}

void W(int x, int y, Value &anser)
{
    //cout << "in W(): ";
    Document::AllocatorType &allocator = Anser.GetAllocator();
    //Value ansdata(kArrayType);
    string str;
    str += matrix[x][y];
    for (int i = x - 1; i >= 0; i--)
    {
        //cout << "in for(" << i << ") ";
        str += matrix[i][y];
        if (dicstionary[(int)(matrix[x][y] - 'a')].HasMember(str.c_str()))
        {
            //cout << "in if ";
            Value key;
            Value val;
            val.SetString(dicstionary[(int)(matrix[x][y] - 'a')][str.c_str()].GetString(), allocator);
            key.SetString(str.c_str(), allocator);
            anser.AddMember(key, val, allocator);
        }
    }
    //cout << "end for" << endl;
}

void S(int x, int y, Value &anser)
{
    //cout << "in W(): ";
    Document::AllocatorType &allocator = Anser.GetAllocator();
    //Value ansdata(kArrayType);
    string str;
    str += matrix[x][y];
    for (int i = x + 1; i < Xnum; i++)
    {
        //cout << "in for(" << i << ") ";
        str += matrix[i][y];
        if (dicstionary[(int)(matrix[x][y] - 'a')].HasMember(str.c_str()))
        {
            //cout << "in if ";
            Value key;
            Value val;
            val.SetString(dicstionary[(int)(matrix[x][y] - 'a')][str.c_str()].GetString(), allocator);
            key.SetString(str.c_str(), allocator);
            anser.AddMember(key, val, allocator);
        }
    }
    //cout << "end for" << endl;
}

void A(int x, int y, Value &anser)
{
    //cout << "in W(): ";
    Document::AllocatorType &allocator = Anser.GetAllocator();
    //Value ansdata(kArrayType);
    string str;
    str += matrix[x][y];
    for (int i = y - 1; i >= 0; i--)
    {
        //cout << "in for(" << i << ") ";
        str += matrix[x][i];
        if (dicstionary[(int)(matrix[x][y] - 'a')].HasMember(str.c_str()))
        {
            //cout << "in if ";
            Value key;
            Value val;
            val.SetString(dicstionary[(int)(matrix[x][y] - 'a')][str.c_str()].GetString(), allocator);
            key.SetString(str.c_str(), allocator);
            anser.AddMember(key, val, allocator);
        }
    }
    //cout << "end for" << endl;
}

void D(int x, int y, Value &anser)
{
    //cout << "in W(): ";
    Document::AllocatorType &allocator = Anser.GetAllocator();
    //Value ansdata(kArrayType);
    string str;
    str += matrix[x][y];
    for (int i = y + 1; i < Ynum; i++)
    {
        //cout << "in for(" << i << ") ";
        str += matrix[x][i];
        if (dicstionary[(int)(matrix[x][y] - 'a')].HasMember(str.c_str()))
        {
            //cout << "in if ";
            Value key;
            Value val;
            val.SetString(dicstionary[(int)(matrix[x][y] - 'a')][str.c_str()].GetString(), allocator);
            key.SetString(str.c_str(), allocator);
            anser.AddMember(key, val, allocator);
        }
    }
    //cout << "end for" << endl;
}

void WA(int x, int y, Value &anser)
{
    //cout << "in W(): ";
    Document::AllocatorType &allocator = Anser.GetAllocator();
    //Value ansdata(kArrayType);
    string str;
    str += matrix[x][y];
    for (int i = x - 1, j = y - 1; i >= 0 && j >= 0; i--, j--)
    {
        //cout << "in for(" << i << ") ";
        str += matrix[i][j];
        if (dicstionary[(int)(matrix[x][y] - 'a')].HasMember(str.c_str()))
        {
            //cout << "in if ";
            Value key;
            Value val;
            val.SetString(dicstionary[(int)(matrix[x][y] - 'a')][str.c_str()].GetString(), allocator);
            key.SetString(str.c_str(), allocator);
            anser.AddMember(key, val, allocator);
        }
    }
    //cout << "end for" << endl;
}

void WD(int x, int y, Value &anser)
{
    //cout << "in W(): ";
    Document::AllocatorType &allocator = Anser.GetAllocator();
    //Value ansdata(kArrayType);
    string str;
    str += matrix[x][y];
    for (int i = x - 1, j = y + 1; i >= 0 && j < Ynum; i--, j++)
    {

        //cout << "in for(" << i << ") ";
        str += matrix[i][j];
        if (dicstionary[(int)(matrix[x][y] - 'a')].HasMember(str.c_str()))
        {
            //cout << "in if ";
            Value key;
            Value val;
            val.SetString(dicstionary[(int)(matrix[x][y] - 'a')][str.c_str()].GetString(), allocator);
            key.SetString(str.c_str(), allocator);
            anser.AddMember(key, val, allocator);
        }
    }
    //cout << "end for" << endl;
}

void SA(int x, int y, Value &anser)
{
    //cout << "in W(): ";
    Document::AllocatorType &allocator = Anser.GetAllocator();
    //Value ansdata(kArrayType);
    string str;
    str += matrix[x][y];
    for (int i = x + 1, j = y - 1; i < Xnum && j >= 0; i++, j--)
    {
        //cout << "in for(" << i << ") ";
        str += matrix[i][j];
        if (dicstionary[(int)(matrix[x][y] - 'a')].HasMember(str.c_str()))
        {
            //cout << "in if ";
            Value key;
            Value val;
            val.SetString(dicstionary[(int)(matrix[x][y] - 'a')][str.c_str()].GetString(), allocator);
            key.SetString(str.c_str(), allocator);
            anser.AddMember(key, val, allocator);
        }
    }
    //cout << "end for" << endl;
}

void SD(int x, int y, Value &anser)
{
    //cout << "in W(): ";
    Document::AllocatorType &allocator = Anser.GetAllocator();
    //Value ansdata(kArrayType);
    string str;
    str += matrix[x][y];
    for (int i = x + 1, j = y + 1; i < Xnum && j < Ynum; i++, j++)
    {
        //cout << "in for(" << i << ") ";
        str += matrix[i][j];
        if (dicstionary[(int)(matrix[x][y] - 'a')].HasMember(str.c_str()))
        {
            //cout << "in if ";
            Value key;
            Value val;
            val.SetString(dicstionary[(int)(matrix[x][y] - 'a')][str.c_str()].GetString(), allocator);
            key.SetString(str.c_str(), allocator);
            anser.AddMember(key, val, allocator);
        }
    }
    //cout << "end for" << endl;
}
