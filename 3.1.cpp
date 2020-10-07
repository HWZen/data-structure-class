#include "pch.h"
#include <stdarg.h>
using namespace std;
using namespace rapidjson;

struct LIST
{
    LIST(){};
    LIST(int num, ...) //This func can receive variable number of function parameters.
    {
        if (num <= 0)
            return;
        va_list arg_ptr;
        va_start(arg_ptr, num);
        LIST *p = this;
        for (int i = 0; i < num; i++)
        {
            strcpy(p->str, va_arg(arg_ptr, char *));
            if (i < num - 1)
            {
                p->next = new LIST;
                p = p->next;
            }
        }
    }
    char str[100];
    LIST *next = NULL;
};

void show_list(LIST &L)
{
    LIST *p = &L;
    while (p != NULL)
    {
        cout << p->str << endl;
        p = p->next;
    }
}

int main()
{
    LIST A_list(5, "Hello", "World!", "This", "is", "A list");
    show_list(A_list);

    return 0;
}

// output:
//
// PS C:\Users\HWZ\GitHub\data-structure-class> ./run.exe
// Hello
// World!
// This
// is
// A list