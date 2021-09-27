#include <iostream>
#include <vector>
using namespace std;


class string_plus : public string
{
public:
    string_plus(const char *str):string(str){}
    string_plus(string str):string(str){}

    inline string_plus operator-(size_t size)
    {
        string_plus tmp = *this;
        tmp.resize(this->size() - size);
        return tmp;
    }

    inline string_plus operator[](size_t size)
    {
        return string_plus(string(this->begin(), this->begin() + size));
    }


};

typedef int *int_p;
void foo(int_p &a, int *b)
{
    a = b;
    b = 0;
}

int main()
{
    int i = 0;
    cout << i++ << " " << ++i << endl;

    int *a = new int(5);
    int *b = new int(10);
    foo(a, b);
    cout << *a << " " << *b << endl;

    string_plus str_p("Hello world");
    cout << str_p - 5 << endl;
    cout << str_p[5] << endl;

    int array[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    void *p = (void *)(array + 1);
    cout << *((int *)p + 1 * sizeof(int)) << endl;
    
}