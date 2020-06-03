#include <iostream>
#include <vector>
#include <string>

void makeBox(int size){

    std::string topper(size, '#');
    std::string section = "##";

    section.insert(1, (size - 2), ' ');

    //Print box
    std::cout << topper << std::endl;
    for (int i=0; i < size - 2; i++){
        std::cout << section << std::endl;
    }
    std::cout << topper << std::endl;
}

int main(int argc, char* argv[]){

    if (argc != 2){
        std::cout << "Must provide one integer for the box size" << std::endl;
        return 1;
    }

    makeBox(std::stoi(argv[1]));


    return 0;
}