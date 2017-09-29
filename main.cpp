#include <iostream>
#include <tinyxml.h>

#include <memory>
#include <base_cpp/non_copyable.h>

class A// : public indigo::NonCopyable
{
public:
    A(int x, double y) : x(x), y(y) {};

    int x;
    double y;
};


A * create_new_A_ptr() {
    return new A(1, 2.0);
}

void create_new_A_write(A& res) {
    new A(1, 2.0);
}



int main() {
    TiXmlDocument doc("C:\\Users\\Daniil_Vodopian\\Documents\\Indigo\\iupac-fsm-parser\\grammar\\alkanes.xml");
    doc.LoadFile();
    fprintf(stdout, "hello");
    doc.Print(stdout, 0);

  


    return 0;
}