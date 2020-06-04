#include <iostream>
#include <string>

class Test{
    public:
        bool foo;
        int bar;
    
    void set_values(bool foo, int bar){

        this->foo = foo;
        this->bar = bar;
    }

    void print_values(){

        std::cout << this->foo << std::endl;
        std::cout << this->bar << std::endl;
    }


};

int main(){

    Test t;

    t.set_values(true, 10);

    t.print_values();

    return 0;
}