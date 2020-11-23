#include "pch.h"
#include <string>
#include <sstream>
#include <fstream>
#include <map>
using namespace std;


class DFA_Table
{
private:
    DFA_Table *HASH_Table[94];
public:
    DFA_Table();
    ~DFA_Table();
    bool find(const string &str);
    bool insert(const string &str);
};

DFA_Table::DFA_Table()
{
    for(int i = 0; i < 94;i++)
        HASH_Table[i] = NULL;
}

DFA_Table::~DFA_Table()
{
    for (int i = 0; i < 94;i++)
        if(HASH_Table[i]!=NULL)
            delete HASH_Table[i];
}

bool DFA_Table::find(const string &str)
{
    DFA_Table *it = this;
    for (int i = 0; i < str.length();i++)
    {
        if (it->HASH_Table[str[i]-'!']==NULL)
            return false;
        else
            it = it->HASH_Table[str[i]-'!'];
    }
    return true;
}

bool DFA_Table::insert(const string &str)
{
    DFA_Table *it = this;
    for (int i = 0; i < str.length();i++)
    {
        if(i==str.length()-1)
            if(it->HASH_Table[str[i]-'!'] !=NULL)
                return true;

        if(it->HASH_Table[str[i]-'!'] == NULL)
            it->HASH_Table[str[i]-'!'] = new DFA_Table;
        it = it->HASH_Table[str[i]-'!'];
    }
    return false;
}



int main()
{
    DFA_Table GFWList;
    // for (int i = 0; i < 64;i++)
    //     char2sub[CH[i]] = i;

    ifstream GFWlist("GFWList.txt");
    assert(GFWlist.is_open());

    string temp;
    while (GFWlist>>temp)
    {
        if (temp[0] != '#')
            GFWList.insert(temp);
    }
    cout << "insert complete." << endl;
    GFWlist.close();

    while (cin >> temp)
    {
        cout << ((GFWList.find(temp)) ? "Proxy" : "Direct") << endl;
    }
    return 0;
}