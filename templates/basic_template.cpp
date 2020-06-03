#include <iostream>
#include <string>

template<typename T>
void Print(T value){
    std::cout << value << std::endl;
}

int main(){

    int a = 5;
    float b = 5.5f;
    std::string c = "Hello";

    Print(a);
    Print(b);
    Print(c);
}